vim ~/.bashrc
# 设置光标形状为 I-beam
echo -e "\e[6 q"
source ~/.bashrc

+---------------------+-----------------+
| 光标形状            | ANSI 转义码     |
+---------------------+-----------------+
| I-beam              | \e[6 q          |
| Block（方块）       | \e[2 q          |
| Underline（下划线） | \e[4 q          |
| Blinking Block      | \e[1 q          |
| Blinking Underline  | \e[3 q          |
+---------------------+-----------------+

