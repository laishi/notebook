hi Normal cterm=NONE ctermfg=8

hi CursorLine term=bold cterm=italic ctermbg=NONE ctermfg=NONE gui=NONE guibg=NONE guifg=NONE
hi CursorLineNr  cterm=bold ctermbg=NONE ctermfg=NONE gui=NONE guibg=NONE guifg=NONE
hi LineNr      term=NONE ctermfg=DarkGray     guifg=Brown
hi VertSplit term=NONE cterm=NONE gui=reverse

" set showmatch
hi MatchParen cterm=NONE ctermbg=DarkBlue ctermfg=White gui=NONE guibg=NONE guifg=NONE

" POP MENU
hi Pmenu          ctermfg=LightGray ctermbg=Black guibg=Magenta
hi PmenuSel       ctermfg=0 ctermbg=7 guibg=Grey
hi PmenuSbar      ctermbg=Black guibg=NONE
hi PmenuThumb     ctermbg=0 guibg=Black



function! SetRandomCTermfg()
    let chigroup = [
          \ 'cLabel',
          \ 'cConditional',
          \ 'cRepeat',
          \ 'cTodo',
          \ 'cBadContinuation',
          \ 'cSpecial',
          \ 'cFormat',
          \ 'cString',
          \ 'cCppString',
          \ 'cSpaceError',
          \ 'cCppSkip',
          \ 'cCharacter',
          \ 'cSpecialError',
          \ 'cSpecialCharacter',
          \ 'cBadBlock',
          \ 'cCurlyError',
          \ 'cErrInParen',
          \ 'cCppParen',
          \ 'cErrInBracket',
          \ 'cCppBracket',
          \ 'cBlock',
          \ 'cParenError',
          \ 'cIncluded',
          \ 'cCommentSkip',
          \ 'cCommentString',
          \ 'cComment2String',
          \ 'cCommentStartError',
          \ 'cUserLabel',
          \ 'cBitField',
          \ 'cOctalZero',
          \ 'cNumber',
          \ 'cFloat',
          \ 'cOctal',
          \ 'cOctalError',
          \ 'cNumbersCom',
          \ 'cParen',
          \ 'cBracket',
          \ 'cNumbers',
          \ 'cWrongComTail',
          \ 'cCommentL',
          \ 'cCommentStart',
          \ 'cComment',
          \ 'cCommentError',
          \ 'cOperator',
          \ 'cType',
          \ 'cTypedef',
          \ 'cStructure',
          \ 'cStorageClass',
          \ 'cConstant',
          \ 'cPreCondit',
          \ 'cPreConditMatch',
          \ 'cCppInIf',
          \ 'cCppInElse',
          \ 'cCppInElse2',
          \ 'cCppOutIf',
          \ 'cCppOutIf2',
          \ 'cCppOutElse',
          \ 'cCppInSkip',
          \ 'cCppOutSkip',
          \ 'cCppOutWrapper',
          \ 'cCppInWrapper',
          \ 'cPreProc',
          \ 'cInclude',
          \ 'cDefine',
          \ 'cMulti',
          \ 'cPragma',
          \ 'cUserCont',
          \ 'cError',
          \ 'cCppOut'
          \]
    for hi in chigroup
        let colorNum = 1 + rand() % 9
        execute "hi " . hi . " cterm=italic ctermfg=" . colorNum
    endfor
endfunction

function! HiOprater()
    let colorNum = 1 + rand() % 9
    syntax match OperatorChars "?\|+\|-\|\*\|;\|:\|,\|<\|>\|&\||\|!\|\~\|%\|=\|)\|(\|{\|}\|\.\|\[\|\]\|/\(/\|*\)\@!"
    exec "hi OperatorChars ctermfg=" . colorNum . " gui=NONE"
endfunction

" 执行函数
call SetRandomCTermfg()



if !exists( 'g:ophigh_highlight_link_group' )
  let g:ophigh_highlight_link_group = ""
endif


let g:OperaterColor = 4
let g:FunctionColor = 5

fun! s:HighlightOperators()
  syntax match CFunction "\s\zs\w\+\ze("
  syntax match OperatorChars "?\|+\|-\|\*\|;\|:\|,\|<\|>\|&\||\|!\|\~\|%\|=\|)\|(\|{\|}\|\.\|\[\|\]\|/\(/\|*\)\@!"


  if g:ophigh_highlight_link_group != ""
    exec "hi link CFunction " . g:ophigh_highlight_link_group
    exec "hi link OperatorChars " . g:ophigh_highlight_link_group
  else
    " exec "hi CFunction guifg=" . g:FunctionColor . " gui=NONE"
    " exec "hi OperatorChars guifg=" . g:OperaterColor. " gui=NONE"

    exec "hi CFunction ctermfg=" . g:FunctionColor. " cterm=NONE"
    exec "hi OperatorChars ctermfg=" . g:OperaterColor. " cterm=NONE"
  endif

endfunction

au Syntax * call s:HighlightOperators()
au ColorScheme * call s:HighlightOperators()
































