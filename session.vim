let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd /disk0/production/fingerspelling_esp32/fingerspelling_
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +1 .
badd +47 main/main.cpp
badd +49 main/NN.cpp
argglobal
%argdel
$argadd .
edit main/main.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
wincmd _ | wincmd |
split
1wincmd k
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 154 + 154) / 309)
exe '2resize ' . ((&lines * 43 + 33) / 66)
exe 'vert 2resize ' . ((&columns * 154 + 154) / 309)
exe '3resize ' . ((&lines * 19 + 33) / 66)
exe 'vert 3resize ' . ((&columns * 154 + 154) / 309)
argglobal
balt .
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 47 - ((46 * winheight(0) + 31) / 63)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 47
normal! 03|
wincmd w
argglobal
if bufexists(fnamemodify("main/NN.cpp", ":p")) | buffer main/NN.cpp | else | edit main/NN.cpp | endif
if &buftype ==# 'terminal'
  silent file main/NN.cpp
endif
balt main/main.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 50 - ((34 * winheight(0) + 21) / 43)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 50
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("term:///disk0/production/fingerspelling_esp32/fingerspelling_//81136:/bin/zsh", ":p")) | buffer term:///disk0/production/fingerspelling_esp32/fingerspelling_//81136:/bin/zsh | else | edit term:///disk0/production/fingerspelling_esp32/fingerspelling_//81136:/bin/zsh | endif
if &buftype ==# 'terminal'
  silent file term:///disk0/production/fingerspelling_esp32/fingerspelling_//81136:/bin/zsh
endif
balt main/NN.cpp
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
let s:l = 3 - ((2 * winheight(0) + 9) / 19)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 3
normal! 066|
wincmd w
2wincmd w
exe 'vert 1resize ' . ((&columns * 154 + 154) / 309)
exe '2resize ' . ((&lines * 43 + 33) / 66)
exe 'vert 2resize ' . ((&columns * 154 + 154) / 309)
exe '3resize ' . ((&lines * 19 + 33) / 66)
exe 'vert 3resize ' . ((&columns * 154 + 154) / 309)
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
