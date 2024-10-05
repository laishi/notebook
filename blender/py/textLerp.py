import bpy
import bl_math
import math
import random
import textgrid
import os

os.system("cls")

class Config:
    def __init__(self, textgridData):
        self.line = True
        self.moveLine = True
        self.useTextGrid = False
        self.timeScale = 1
        self.frames = [50, 32, 20, 15, 38, 23, 32, 22, 19, 29, 20, 25, 15, 16, 12, 24, 25, 14, 16, 25, 14, 16, 19, 9, 20, 25, 32, 20, 15, 38, 23, 32, 22, 19, 29, 20, 25, 15, 16, 12, 24, 25, 14, 16, 25, 14, 16, 19, 9, 20, 25]
        self.lineSpaceFrame = 20
        self.textSpace = 0.5
        
        
        self.init()
        
    def init(self):
        self.useTextGridFrames()
        
    def useTextGridFrames(self):
        self.frames = [int(item*self.timeScale) for item in self.frames]
        if self.useTextGrid:
            self.frames = textgridData.frames



class TextgridData:
    def __init__(self):
        self.gridPath = r'C:\Users\laish\SurfaceStudio\Work\Blender\textGrid\我的星座.TextGrid'
        self.fps = bpy.context.scene.render.fps
        self.frames = []
        
        self.init()
        
    def init(self):        
        self.getFrames()        
        
    def getFrames(self):
        tg = textgrid.TextGrid.fromFile(self.gridPath)

        textgridJson = []
        frames = []
        for item in tg[0]:
            obj = {}    
            if len(item.mark.strip()) == 1 and len(item.mark)==1:         
                obj['start'] = int(item.minTime * self.fps)
                obj['end'] = int(item.maxTime * self.fps)
                obj['text'] = item.mark
                frames.append(obj['end'] - obj['start'])
                textgridJson.append(obj)                
        self.frames = frames
        
        
class TextLineData:
    def __init__(self, config, gpName):
        self.gpName = gpName
        self.line = config.line
        self.textSpace = config.textSpace
        
        self.firstPose = 0.0
        self.lineTexts = []
        
        self.init()
        
    def init(self):
        self.textLine()      
    
    def getLayer(self):
        gPlayers = bpy.data.grease_pencils[self.gpName].layers[0]
        return gPlayers
    
    def getFrame(self):
        gpFrame = self.getLayer().frames[0]
        return gpFrame

    def getStrokes(self):
        gpStrokes = self.getFrame().strokes
        return gpStrokes


    def getStrokeDist(self):
        strokes = self.getFrame().strokes
        center = []
        distance = []
        for stroke in strokes:
            boundMin = stroke.bound_box_min
            boundMax = stroke.bound_box_max
            center.append((boundMax + boundMin) / 2)            
        for i in range(len(center)-1):
            start = center[i]
            end = center[i+1]
            dist = (end-start).length

            distance.append(dist)
        return {'distance': distance, 'center': center}
    
    
    def sortLineText(self, strokesList, pos, axial="x"):
        unique_pos = list(set(pos))            

        rows = [[] for _ in range(len(unique_pos))]
        for i in range(len(pos)):
            rows[unique_pos.index(pos[i])].append(strokesList[i])
            
        for i in range(len(rows)):
            row = rows[i]
            sortIndex = []
            texts = []
            for text in row:
                if axial == "x":
                    sortIndex.append(int(abs(text[0].bound_box_min.z)))
                if axial == "z":
                    sortIndex.append(int(abs(text[0].bound_box_min.x)))
                texts.append(text)
            
            sorted_texts = [x for _, x in sorted(zip(sortIndex, texts))]
            rows[i] = sorted_texts
            
        self.lineTexts = rows
        return rows
    

    def textStrokes(self):
        strokes = self.getFrame().strokes
        distance = self.getStrokeDist()['distance']
        splitpos = [0]
        for i in range(len(distance)):
            if distance[i] > self.textSpace:
                splitpos.append(i+1)
        splitpos.append(len(distance)+1)
        strokesList = []
        for i in range(len(splitpos)-1):
            s = splitpos[i]
            e = splitpos[i+1]
            strokesList.append(strokes[s:e])
        textsCenter = []
        for strokes in strokesList:
            centers = []
            for stroke in strokes:
                boundMin = stroke.bound_box_min
                boundMax = stroke.bound_box_max
                center = (boundMax + boundMin) / 2
                centers.append(list(center))
            textCenter = [sum(coord) / len(centers) for coord in zip(*centers)]
            textsCenter.append(textCenter)

        xpos = []
        zpos = []
        for center in textsCenter:
            x = center[0]
            z = center[2]
            xpos.append(abs(int(x)))
            zpos.append(abs(int(z)))
        self.firstPose = int(xpos[0])  
        
        
        if self.line:
            unique_xpos = list(set(xpos))
            rows = [[] for _ in range(len(unique_xpos))]        
            for i in range(len(xpos)):
                rows[unique_xpos.index(xpos[i])].append(strokesList[i])                
        else:            
            unique_zpos = list(set(zpos))
            rows = [[] for _ in range(len(unique_zpos))]        
            for i in range(len(zpos)):
                rows[unique_zpos.index(zpos[i])].append(strokesList[i])
                
        self.lineTexts = rows                
        return {"textStroke": strokesList, "lineTexts": rows}
        
        
              
        
#        if self.line:
#            rows = self.sortLineText(strokesList, xpos, axial="x")            
#        else:
#            rows = self.sortLineText(strokesList, zpos, axial="z")

#        self.lineTexts = rows
#        return {"textStroke": strokesList, "lineTexts": rows}

    def textLine(self):
        textStrokeNumber = 0
        textStrokesData = self.textStrokes()
        lineTexts = textStrokesData['lineTexts']
        for texts in lineTexts:
            for text in texts:
                textStrokeNumber = len(text)

class TextLerp:
    def __init__(self, config, lineTexts):
        self.attrs = ['co', 'time', 'pressure', 'strength', 'uv_rotation', 'vertex_color']
        self.line_width = bpy.data.brushes['Pencil'].size
        self.gpname = 'lerpGP'
        self.moveLine = config.moveLine
        self.line = config.line
        self.frames = config.frames
        self.endLineFrame = 0

        self.info = {}

        self.init()

    def init(self):
        self.textLerp()
        
    def resample(self, attr, sample_num):
        if sample_num < 2:
            return attr

        dimension = len(attr[0]) if isinstance(attr[0], (list, tuple)) else 1
        step = (len(attr) - 1) / (sample_num - 1)
        result = []
        for i in range(sample_num):
            index1 = int(i * step)
            index2 = min(index1 + 1, len(attr) - 1)
            alpha = i * step - index1
            if dimension == 1:
                interpolated_value = (1 - alpha) * attr[index1] + alpha * attr[index2]
            else:
                interpolated_value = [
                    (1 - alpha) * attr[index1][j] + alpha * attr[index2][j] for j in range(dimension)
                ]
            result.append(interpolated_value)
        return result
    
    
    
    def lerp(self, position1, position2, interpolation_factor, frequency=1, amplitude=0.0):
        dimension = len(position1) if isinstance(position1, (list, tuple)) else 1
        
        if dimension == 1:
            interpolated_position = position1 + (position2 - position1) * interpolation_factor

        elif dimension == 3:
            # Calculate the sinusoidal offset for each axis
            offset = [amplitude * math.sin(2 * math.pi * frequency * interpolation_factor) for _ in range(3)]
            interpolated_position = [
                position1[0] + (position2[0] - position1[0]) * interpolation_factor + offset[0],
                position1[1] + (position2[1] - position1[1]) * interpolation_factor + offset[1],
                position1[2] + (position2[2] - position1[2]) * interpolation_factor + offset[2]
            ]
        elif dimension == 4:
            # Calculate the sinusoidal offset for each axis
            offset = [amplitude * math.sin(2 * math.pi * frequency * interpolation_factor) for _ in range(4)]
            interpolated_position = [
                position1[0] + (position2[0] - position1[0]) * interpolation_factor + offset[0],
                position1[1] + (position2[1] - position1[1]) * interpolation_factor + offset[1],
                position1[2] + (position2[2] - position1[2]) * interpolation_factor + offset[2],
                position1[3] + (position2[3] - position1[3]) * interpolation_factor + offset[3]
            ]
        else:
            raise ValueError("Unsupported dimension: {}".format(dimension))

        return interpolated_position
    
                
    def textsInfo(self, lineText):
        pointNum = 0
        textAttrs = {"co": [], "time": [], "pressure": [], "strength": [], "uv_rotation": [], "vertex_color": []}
        info = {"textPointNum": [], "textDistance": 0, "strokeDistance": [], "percentageDist": [], "strengthTotal": 0}
        for strokes in lineText:
            textNumber = []
            for stroke in strokes:
                points = stroke.points
                textNumber.append(len(points))
                strokeCo = []
                strokeTime = []
                strokePressure = []
                strokeStrength = []
                strokeUv_rotation = []
                strokeVertex_color = []
                
                strokeDist = 0
                for i in range(len(points)):
                    point = points[i]
                    co = [point.co.x, point.co.y, point.co.z]
                    vertex_color = [point.vertex_color[0], point.vertex_color[1], point.vertex_color[2], point.vertex_color[3]]
                    strokeCo.append(co)
                    strokeTime.append(point.time)
                    strokePressure.append(point.pressure)
                    strokeStrength.append(point.strength)
                    strokeUv_rotation.append(point.uv_rotation)
                    strokeVertex_color.append(vertex_color)
                    
                    if i < len(points)-1:
                        point1 = points[i]
                        point2 = points[i+1]
                        co1 = [point1.co.x, point1.co.y, point1.co.z]
                        co2 = [point2.co.x, point2.co.y, point2.co.z]
                        dist = ((co2[0] - co1[0]) ** 2 + (co2[1] - co1[1]) ** 2 + (co2[2] - co1[2]) ** 2) ** 0.5
                        strokeDist += dist
                        
                info["strokeDistance"].append(strokeDist)
                info["textDistance"] += strokeDist
                info["strengthTotal"] += sum(strokeStrength)
                                            
                textAttrs["co"].append(strokeCo)
                textAttrs["time"].append(strokeTime)
                textAttrs["pressure"].append(strokePressure)
                textAttrs["strength"].append(strokeStrength)
                textAttrs["uv_rotation"].append(strokeUv_rotation)
                textAttrs["vertex_color"].append(strokeVertex_color)
                
            info["textPointNum"].append(textNumber)
            
        for dist in info["strokeDistance"]:
            percentage = dist / info["textDistance"]
            info["percentageDist"].append(percentage)
                
        attrs = {"info": info, "textAttrs": textAttrs}
        return attrs
    
    
    def textResample(self, text1, text2):
        
        if len(text2) > 1: #merge text2
            text2 = [[item for sublist in text2 for item in sublist]]
            
        # 获取text info
        text1_info = self.textsInfo(text1)["info"]
        text2_info = self.textsInfo(text2)["info"]
        textPointNum1 = text1_info["textPointNum"]
        textPointNum2 = text2_info["textPointNum"]

        
        textPointSum1 = sum(sum(sublist) for sublist in textPointNum1)
        textPointSum2 = sum(sum(sublist) for sublist in textPointNum2)
        sampleMax = max(textPointSum1, textPointSum2)

        
        sampleText, targetText = (text1, text2) if textPointSum1 < sampleMax else (text2, text1)
        targetSampleNum = textPointNum2 if textPointSum1 < sampleMax else textPointNum1

            
        sampleTextAttrs = self.textsInfo(sampleText)["textAttrs"]
        textPercentageDist = self.textsInfo(sampleText)["info"]["percentageDist"]
        
        sampleNumbers = [int(dist * sampleMax) for dist in textPercentageDist]
        difSampleNum = sampleMax - sum(sampleNumbers)
        if difSampleNum > 0:
            for i in range(difSampleNum):
                sampleNumbers[i - difSampleNum] += 1
                
        # 重新抽样并组合样本
        splitAttrs = {
            'co': [],
            'time': [],
            'pressure': [],
            'strength': [],
            'uv_rotation': [],
            'vertex_color': []
        }
        
        for idx, attr_name in enumerate(['co', 'time', 'pressure', 'strength', 'uv_rotation', 'vertex_color']):
            textData = []
            attr_data = sampleTextAttrs[attr_name]
            for i in range(len(sampleNumbers)):
                num = sampleNumbers[i]
                strokeData = attr_data[i]
                attr_data_resampled = self.resample(strokeData, num)
                textData.extend(attr_data_resampled)            

            startNum = 0
            targetSample = targetSampleNum[0]
            
            for i in range(len(targetSample)):
                num = targetSample[i] + startNum
                strokeData = textData[startNum: num]
                splitAttrs[attr_name].append(strokeData)
                startNum = num
                        
        targetAttrs = self.textsInfo(targetText)["textAttrs"]       

        if textPointSum1 < sampleMax:        
            lerpText = [splitAttrs, targetAttrs]
        else:
            lerpText = [targetAttrs, splitAttrs]        

        return lerpText


    def textSplit(self, text1, text2):

        textPointNum = []
        sourceTextAttrs = []

        for textSource in text1:
            textSource = [textSource]
            textSource_info = self.textsInfo(textSource)["info"]
            textSource_attrs = self.textsInfo(textSource)["textAttrs"]
            pointNum = sum(textSource_info["textPointNum"][0])
            textPointNum.append(pointNum)
            sourceTextAttrs.append(textSource_attrs)
                    
        if len(text1) > 1:
            
            sourceText = [[item for sublist in text1 for item in sublist]]            
            # 获取sourText的信息
            sourceText_info = self.textsInfo(sourceText)["info"]                      

            sourcePointNum = sourceText_info["textPointNum"]
            sourcePointNum = [sum(item) for item in sourcePointNum]
            SourceSampleMax = sum(sourcePointNum)

            # 获取text2的信息
            splitTextAttrs = self.textsInfo(text2)["textAttrs"]
            splitTextInfo = self.textsInfo(text2)["info"]

            # 计算样本分割数目
            splitPercentageDist = splitTextInfo["percentageDist"]
            sampleNumbers = [int(dist * SourceSampleMax) for dist in splitPercentageDist]

            # 调整样本数量以适应总数
            difSampleNum = SourceSampleMax - sum(sampleNumbers)
            if difSampleNum > 0:
                for i in range(difSampleNum):
                    sampleNumbers[i - difSampleNum] += 1

            # 重新抽样并组合样本
            newAttrs = []
            splitAttrs = {
                'co': [],
                'time': [],
                'pressure': [],
                'strength': [],
                'uv_rotation': [],
                'vertex_color': []
            }
            
            
            for idx, attr_name in enumerate(['co', 'time', 'pressure', 'strength', 'uv_rotation', 'vertex_color']):
                textData = []
                attr_data = splitTextAttrs[attr_name]
                for i in range(len(sampleNumbers)):
                    num = sampleNumbers[i]
                    strokeData = attr_data[i]
                    attr_data_resampled = self.resample(strokeData, num)
                    # this add strength code
                    textData.extend(attr_data_resampled)

                startNum = 0
                for i in range(len(textPointNum)):
                # 按照textPointNum将文本分割
                    num = textPointNum[i] + startNum
                    data = textData[startNum: num]                
                    splitAttrs[attr_name].append(data)
                    startNum = num
                            
            targetTextAttrs = []        
            for i in range(len(textPointNum)):
                new_attr = {
                    'co': [],
                    'time': [],
                    'pressure': [],
                    'strength': [],
                    'uv_rotation': [],
                    'vertex_color': []
                }
                for key, value in splitAttrs.items():
                    new_attr[key].append(value[i])
                targetTextAttrs.append(new_attr)               

            #text1 = [[item for sublist in text1 for item in sublist]]

            textAttrs = []
            for i in range(len(sourceTextAttrs)):
                source = sourceTextAttrs[i]
                target = targetTextAttrs[i]
                textAttrs.append([source, target])

            return textAttrs

    def textData(self, text):        
        textStrokeNum = len(text)                
        textPointNum = 0
        textDistance = 0
        textStrokeDistance = []
        distancePercentage = []

        for n in range(len(text)):
            textPointNum += len(text[n].points)
            sd = 0

            for m in range(len(text[n].points)-1):
                point1 = text[n].points[m]
                point2 = text[n].points[m+1]

                dist = (point2.co - point1.co).length
                sd += dist                

            textDistance += sd
            textStrokeDistance.append(sd)
            
        for dist in textStrokeDistance:
            distancePercentage.append(dist/textDistance)

        td = {
            "textStrokeNum": textStrokeNum,
            "textPointNum": textPointNum,
            "textDistance": textDistance,
            "textStrokeDistance": textStrokeDistance,
            "distancePercentage": distancePercentage,
        }
        return td

    

    def remove_gp(self, name):
        for gp in bpy.data.grease_pencils:
            if gp.name == name:
                bpy.data.grease_pencils.remove(gp)

    def add_materials(self, gpencil):
        mat = bpy.data.materials.get('Dots Stroke')
        if mat:
            gpencil.data.materials.append(mat)
     
    def lineTexts(self):

        lineTextsAttr = []
        for index in range(len(lineTexts)-1):
            line1 = lineTexts[index]
            line2 = lineTexts[index+1]
            lenLine1 = len(line1)
            lenLine2 = len(line2)
            minLen = min(lenLine1, lenLine2)
            maxLen = max(lenLine1, lenLine2)
            diff = maxLen - minLen
            splitPoint = minLen-1            
            
            lineTextAttr = []
            for i in range(minLen):
                text1 = []
                text2 = []
                textAttr1 = {}
                textAttr2 = {}
                if i < splitPoint:
                    text1 = line1[i:i+1]
                    text2 = line2[i:i+1]
                else:
                    text1 = line1[splitPoint:]
                    text2 = line2[splitPoint:]                
                
                if len(text1) <= len(text2):
                    sourceTarget = self.textResample(text1, text2)
                    lineTextAttr.append(sourceTarget)
                else:
                    sourceTarget = self.textSplit(text1, text2)
                    lineTextAttr.extend(sourceTarget)
            lineTextsAttr.append(lineTextAttr)
                    
        return lineTextsAttr
                    
    def lerpAttr(self, gpLayer, strokePoints, sourceTextAttr, idx, targetTextAttr, frameStart, frameEnd, frame, fractor):
        
        gpFrame = gpLayer.frames.new(frame)
        newStroke = gpFrame.strokes.new()
        newStroke.line_width = self.line_width                
        newStroke.points.add(strokePoints)                    
        frameFactor = (frame-frameStart) / (frameEnd-frameStart)                    
        
        for i in range(strokePoints):
            idxfac = idx/(strokePoints-1) * -1 #整个字整体变换
            idxfac = i/(strokePoints-1) * -1 
            framelerp = bl_math.lerp(0, 2, frameFactor)
            fractor = bl_math.clamp(idxfac+framelerp)

            for attr in self.attrs:
                sa = sourceTextAttr[attr][i]
                ta = targetTextAttr[attr][i]
                lerpAttr = self.lerp(sa, ta, fractor)
                if attr != 'time':
                    setattr(newStroke.points[i], attr, lerpAttr)             

    def textLerp(self):
        lineTextsAttr = self.lineTexts()
        
        self.remove_gp(self.gpname)
        gpencil_data = bpy.data.grease_pencils.new(self.gpname)
        gpencil = bpy.data.objects.new(gpencil_data.name, gpencil_data)
        bpy.context.collection.objects.link(gpencil)
        self.add_materials(gpencil)
        
        frameIndex = 0
        frameStart = 10
        framesStart = []
        framesEnd = []      
        lineTextNumber = [0]
        print("len(lineTextsAttr): ", len(lineTextsAttr))
        for index in range(len(lineTextsAttr)):            
            lineTextAttr = lineTextsAttr[index]            
            lineTextCount = len(lineTextAttr)

            if index == 0:
                lineTextNumber[0] = lineTextCount
            else:
                lineTextNumber.append(lineTextNumber[-1] + lineTextCount)

            for idx in range(len(lineTextAttr)):
                framesStart.append(frameStart)
                frameEnd = self.frames[frameIndex] + frameStart - 1
                framesEnd.append(frameEnd)
                if idx == len(lineTextAttr)-1:                    
                    frameStart = frameEnd + config.lineSpaceFrame
                else:
                    frameStart = frameEnd + 0
                frameIndex += 1
        
        bpy.context.scene.frame_end = framesEnd[-1] + 10
        bpy.ops.screen.animation_cancel()
        bpy.ops.screen.animation_play()

        textIndex = 0        
        for index in range(len(lineTextsAttr)):            
            lineTextAttr = lineTextsAttr[index]            
            beforeLineTextLen = len(lineTextsAttr[index-1])
            currentLineTextLen = len(lineTextAttr)            
            
            for idx in range(len(lineTextAttr)):                
                textAttr = lineTextAttr[idx]
                strokePoints = len([attr for sublist in textAttr[0]['co'] for attr in sublist])
                
                sourceText = textAttr[0]
                targetText = textAttr[1]
                
                sourceTextAttr = {}            
                for key, value in sourceText.items():                
                    values = []
                    for attrs in value:
                        for i in range(len(attrs)):
                            val = attrs[i]
                            if self.moveLine:
                                if key == 'co':
                                    if self.line:
                                        xco = val[0] - int(val[0])
                                        values.append([xco, val[1], val[2]])
                                    else:
                                        zco = val[2] - int(val[2])
                                        values.append([val[0], val[1], zco])
                                else:
                                    values.append(val)
                            else:
                                values.append(val)
                                
                    sourceTextAttr[key] = values
                    
                targetTextAttr = {}
                firstposx = 0
                for key, value in targetText.items():                
                    values = []
                    for attrs in value:
                        for i in range(len(attrs)):
                            val = attrs[i]
                            if self.moveLine:
                                if key == 'co':
                                    if self.line:
                                        xco = val[0] - int(val[0])
                                        values.append([xco, val[1], val[2]])
                                    else:
                                        zco = val[2] - int(val[2])
                                        values.append([val[0], val[1], zco])
                                else:
                                    values.append(val)
                            else:
                                values.append(val)
                                
                    targetTextAttr[key] = values

                layerName = "lerpLayer" + str(index+1) + '_' + str(idx)
                try:
                    gpLayer = bpy.data.grease_pencils['lerpGP'].layers[idx]
                    #print("Layer found:", gpLayer)
                except IndexError:
                    #print("Index out of range. No layer found.")
                    gpLayer = bpy.data.grease_pencils['lerpGP'].layers.new(layerName)

                    
                # INIT FRAME
                if index == 0:
                    gpFrame = gpLayer.frames.new(1)
                    newStroke = gpFrame.strokes.new()
                    newStroke.line_width = self.line_width                
                    newStroke.points.add(strokePoints)                    
                    fractor = 0                    
                    for i in range(strokePoints):
                        for attr in self.attrs:
                            sa = sourceTextAttr[attr][i]
                            if attr != 'time':
                                setattr(newStroke.points[i], attr, sa)


                frameStart = framesStart[textIndex]
                frameEnd = framesEnd[textIndex]
                for frame in range(frameStart, frameEnd+1):
                    if frame > 1:     
                        gpFrame = gpLayer.frames.new(frame)
                        newStroke = gpFrame.strokes.new()
                        newStroke.line_width = self.line_width                
                        newStroke.points.add(strokePoints)                    
                        frameFactor = (frame-frameStart) / (frameEnd-frameStart)
                        
                        for i in range(strokePoints):
                            idxfac = idx/(strokePoints-1) * -1 #整个字整体变换
                            idxfac = i/(strokePoints-1) * -1 
                            framelerp = bl_math.lerp(0, 2, frameFactor)
                            fractor = bl_math.clamp(idxfac+framelerp)

                            for attr in self.attrs:
                                sa = sourceTextAttr[attr][i]
                                ta = targetTextAttr[attr][i]
                                lerpAttr = self.lerp(sa, ta, fractor)
                                if attr != 'time':
                                    setattr(newStroke.points[i], attr, lerpAttr)
                            
                # TEXT DEBUG

                if currentLineTextLen > beforeLineTextLen and index > 0:
                    difLen = currentLineTextLen - beforeLineTextLen
                    preLineTextNumber = lineTextNumber[index]
                    frame = framesStart[preLineTextNumber-difLen-1]

                    for i in range(difLen):
                        layerIndex = beforeLineTextLen + i
                        if layerIndex == idx:                            
                            gpLayer = bpy.data.grease_pencils['lerpGP'].layers[layerIndex]
                            
                            gpFrame = gpLayer.frames.new(frame)
                            newStroke = gpFrame.strokes.new()
                            newStroke.line_width = self.line_width                
                            newStroke.points.add(strokePoints)                    
                            fractor = 0                  
                            for i in range(strokePoints):
                                for attr in self.attrs:
                                    sa = sourceTextAttr[attr][i]
                                    ta = targetTextAttr[attr][i]
                                    lerpAttr = self.lerp(sa, ta, fractor)
                                    if attr != 'time':
                                        setattr(newStroke.points[i], attr, lerpAttr)
                                        


                if currentLineTextLen < beforeLineTextLen and index > 0 and idx == 0:
                    difLen = beforeLineTextLen - currentLineTextLen
                    currentLineTextNumber = lineTextNumber[index]
                    frame = framesStart[currentLineTextNumber - 1]

                    for i in range(difLen):
                        layerIndex = currentLineTextLen + i
                        gpLayer = bpy.data.grease_pencils['lerpGP'].layers[layerIndex]
                        gpFrame = gpLayer.frames.new(frame)

                textIndex += 1
                
textgridData =  TextgridData()           
config =  Config(textgridData)
         

linesTexts = TextLineData(config, "GPWrite")
lineTexts = linesTexts.lineTexts

print("lineTexts: ", lineTexts)
print("len lineTexts: ", len(lineTexts))

TextLerp(config, lineTexts)