# CLI colors
export CLICOLOR=1

export PS1='\u\w: '

# use bold blue for dir’s
export LSCOLORS=Exfxcxdxbxegedabagacad

# do not bell on tab-completion
bind 'set bell-style visible'
#"set bell-style visible"

# some git pimpin
function parse_git_branch {
  git branch --no-color 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
}
 
function proml {
  local        BLUE="\[\033[0;34m\]"
  local        BLACK="\[\033[0;30m\]"
  case $TERM in
    xterm*)
    TITLEBAR='\u\w\007\]'
    ;;
    *)
    TITLEBAR="\u\w"
    ;;
  esac
 
PS1="${TITLEBAR}\
$BLUE[\$(parse_git_branch)$BLUE]\
$BLACK\$ "
PS2='> '
PS4='+ '
}
proml


# Alias
alias ll="ls -alo"
alias rmb="/bin/rm -r *~"
alias psg="ps auxww | grep"
alias scons="/usr/local/bin/scons"
alias makeself="/Users/ulf/bin/makeself-2.1.5/makeself.sh"
alias p4merge="/Application/p4merge.app/Contents/MacOS/p4merge $*"
alias p4diff="[ $# -eq 7 ] && /usr/local/bin/p4merge "$2" "$5" "

#alias llvm-as="/Users/ulf/Dev/svn/llvm/trunk/Debug/llvm-as"
#alias llc="/Users/ulf/Dev/svn/llvm/trunk/Debug/llc"

# History handling
#
# Erase duplicates
export HISTCONTROL=erasedups
# resize history size
export HISTSIZE=10000
# append to bash_history if Terminal.app quits
shopt -s histappend

# Mac ports
export PATH=/opt/local/bin:/opt/local/sbin:$PATH

PATH=$PATH:$HOME/bin
PATH=$PATH:$HOME/Dev/svn/llvm/trunk/Debug/bin
