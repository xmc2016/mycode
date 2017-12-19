set nocompatible

if filereadable(expand("~/.vimrc.bundles"))
	source ~/.vimrc.bundles
endif

map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
	exec "w"
	if &filetype == 'c'
		exec "!g++ % -o %<"
		exec "!time ./%<"
		exec "!time ./%<"
	elseif &filetype == 'java' 
		exec "!javac %" 
		exec "!java %<"
	elseif &filetype == 'sh'
		:! bash %
	elseif &filetype == 'python'
		exec "!python %"
	elseif &filetype == 'html'
		exec "!firefox % &"
	endif
endfunc

set completeopt=longest,menu
filetype on 
"新建.c,.h,.sh,.py自动插入文件头
autocmd BufNewFile *.cpp,*.[ch],*.sh,*.py,*.java exec ":call SetTitle()"
"定义函数SetTitle自动插入文件头 
func SetTitle()
	if &filetype == 'sh'
		call setline(1,"\#########################################################################") 
		call append(line("."), "\# File Name: ".expand("%")) 
		call append(line(".")+1, "\# Author: xmc") 
		call append(line(".")+2, "\# mail: 1649214962@qq.com") 
		call append(line(".")+3, "\# Created Time: ".strftime("%c")) 
		call append(line(".")+4, "\#########################################################################") 
		call append(line(".")+5, "\#!/bin/bash") 
		call append(line(".")+6, "")
	elseif &filetype == 'python'
		call setline(1,"\#########################################################################") 
		call append(line("."), "\# File Name: ".expand("%")) 
		call append(line(".")+1, "\# Author: xmc") 
		call append(line(".")+2, "\# mail: 1649214962@qq.com") 
		call append(line(".")+3, "\# Created Time: ".strftime("%c")) 
		call append(line(".")+4, "\#########################################################################") 
		call append(line(".")+5, "\#!/home/xmc/.pyenv/shims/python") 
		call append(line(".")+6, "")
	else 
		call setline(1, "/*************************************************************************") 
		call append(line("."), "	> File Name: ".expand("%")) 
		call append(line(".")+1, "	> Author:xmc") 
		call append(line(".")+2, "	> Mail:1649214962qq.com") 
		call append(line(".")+3, "	> Created Time: ".strftime("%c")) 
		call append(line(".")+4, " ************************************************************************/") 
	endif
	if &filetype == 'cpp'
		call append(line(".")+5, "#include<iostream>")
		call append(line(".")+6, "using namespace std;")
		call append(line(".")+7, "")
	endif
	if &filetype == 'c'
		call append(line(".")+5, "#include<stdio.h>")
		call append(line(".")+6, "")
	endif

endfunc 
autocmd BufNewFile * normal G

syntax on
set nu
"代码补全
set completeopt=preview,menu 
"高亮显示匹配的括号
set showmatch
"匹配括号高亮的时间（十分之一秒）
set matchtime=1
"
"自动缩进
set autoindent
"Tab 键宽度为4
set tabstop=4
"统一缩进为4
set softtabstop=4
set shiftwidth=4
"不要用空格代替制表符
set noexpandtab
"在行和段开始时使用制表符
set smarttab
"鼠标可以移动光标
set mouse=a 
"共享剪切板
set clipboard+=unnamed
"set ruler   "打开状态栏标尺
set cursorline "突出显示当前行
"允许backspace和光标跨行边界
set whichwrap+=<,>,h,l
""去掉输入错误提示音
set noeb
"使回车键正常处理indent，eol，start等
set backspace=2
""打开文件类型检查
filetype plugin on
""为特定的文件载入相关的缩进文件
filetype indent on
""带有如下符号的单词不要被换行分割
set iskeyword+=_,$,@,%,#,-
"从不备份
set nobackup
