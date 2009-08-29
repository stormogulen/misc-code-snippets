;;
;; -*- Emacs-Lisp -*-
;; -----------------------------------------------------------------------------
;; custom.el
;; -----------------------------------------------------------------------------

(require 'font-lock) ; enable syntax highlighting

(setq custom-file
      (expand-file-name "custom.el"
			(expand-file-name ".xemacs" "~")))

;;;
(custom-set-variables)

; Syntax highlighting. Light background.
; Insert this in custom.el. Then restart XEmacs.

(custom-set-faces ; only one 'custom-set-faces' entry must exist in custom.el
 '(default ((t (:foreground "#000000" :background "#FFFFFF" :size "12" :family "courier"))) t)
 '(cperl-array-face ((t (:foreground "orangered" :bold t))))
 '(cperl-hash-face ((t (:foreground "Red" :bold t))))
 '(cperl-nonoverridable-face ((t (:foreground "orange" :bold t))))
 '(custom-button-face ((t (:bold t :foreground "#3fdfcf"))))
 '(custom-group-tag-face ((t (:underline t :foreground "blue"))))
 '(custom-saved-face ((t (:underline t :foreground "orange"))))
 '(custom-state-face ((t (:foreground "green3"))))
 '(custom-variable-button-face ((t (:bold t :underline t :foreground "white"))))
 '(dired-face-permissions ((t (:foreground "green3"))))
 '(font-lock-comment-face ((t (:foreground "#ee7600"))))
 '(font-lock-doc-string-face ((t (:foreground "green3"))))
 '(font-lock-function-name-face ((t (:foreground "blue" :bold t))))
 '(font-lock-keyword-face ((t (:foreground "#f939ff"))))
 '(font-lock-preprocessor-face ((t (:foreground "red"))))
 '(font-lock-reference-face ((t (:foreground "green3"))))
 '(font-lock-string-face ((t (:foreground "green3"))))
 '(font-lock-type-face ((t (:foreground "#886fff" :bold t))))
 '(font-lock-variable-name-face ((t (:foreground "#9a2fff" :bold t))))
 '(font-lock-warning-face ((t (:foreground "Violetred" :bold t))))
 '(highlight ((t (:foreground "red3" :background "white"))) t)
 '(isearch ((t (:foreground "red" :background "white"))) t)
 '(list-mode-item-selected ((t (:foreground "green3"))) t)
 '(message-cited-text ((t (:bold t))))
 '(secondary-selection ((t (:foreground "white" :background "red"))) t)
 '(text-cursor ((t (:foreground "black" :background "green3"))) t)
 '(zmacs-region ((t (:background "RoyalBlue"))) t)
)
;;;

(setq user-full-name "Ulf Ejlertsson")

;; y istället för yes
(fset 'yes-or-no-p 'y-or-n-p)

;; Sets the time format to 24hr format
(setq display-time-24hr-format t)

;;; Displays time, date and system load in the mode-line
(display-time)

;;; Displays the column number in the mode-line
(display-column-mode t)

;;; Displays the line number in the mode-line
(line-number-mode t)

;;; matchande parenteser
(paren-set-mode 'paren)

;;; kompileringsfönster
(setq compilation-window-height 10)

;;; inget pip
(setq visible-bell t)

;;; alltid newline
(setq require-final-newline t)

;;; stanna vid sista raden
(setq next-line-add-newlines nil)

;; wheel mouse
(global-set-key [mouse-4] 'scroll-down)
(global-set-key [mouse-5] 'scroll-up)

;; scrolla rad för rad istället för stora steg
;;(setq scroll-step 1)
(set-variable 'scroll-conservatively 5)

;; ingen "splash screen" när man startar
(setq inhibit-splash-screen t)

;;; indentera automatiskt, genom att byta plats på RET och LF
(setq foo (global-key-binding "\C-m"))
(global-set-key "\C-m" (global-key-binding "\C-j"))
(global-set-key "\C-j" foo)

';;; Öppna oidentifierade filer i textläge
(setq default-major-mode 'text-mode)

;;; ladda lite olika 'modes'
;; my elisp packages
;(add-to-list 'load-path "~/.xemacs/elisp")
;(add-to-list 'load-path "elisp/glsl-mode.el")
;(add-to-list 'load-path "elisp/OpenGL.el")
;(add-to-list 'load-path "elisp/cg-mode.el")
;(add-to-list 'load-path "elisp")




;;; HTML Tidy
(autoload 'tidy-buffer "tidy" "Run Tidy HTML parser on current buffer" t)
(autoload 'tidy-region "tidy" "Run Tidy HTML parser on current region" t)
(autoload 'tidy-parse-config-file "tidy" "Parse the `tidy-config-file'" t)
(autoload 'tidy-save-settings "tidy" "Save settings to `tidy-config-file'" t)
(add-hook 'html-mode-hook #'(lambda () (local-set-key [(control x) (t)] 'tidy-buffer) ))
(add-hook 'html-helper-mode-hook #'(lambda () (local-set-key [(control x) (t)] 'tidy-buffer) ))

;; Objective C
(autoload 'objc-mode "cc-mode" "Objective-C Editing Mode" t)

;; C/C++
(require 'cc-mode)

(setq auto-mode-alist
      (append '(("\\.C$"   . c++-mode)
		("\\.ipp$" . c++-mode)
		)
	      auto-mode-alist))



;;
;; Indentering för namespace
;;
(defun my-c-namespace-open-indent (langelem)
  "Used with c-set-offset, indents namespace opening braces to the same indentation as the line on which the namespace declaration starts."
  (save-excursion
    (goto-char (cdr langelem))
    (let ((column (current-column)))
      (beginning-of-line)
      (skip-chars-forward " \t")
      (- (current-column) column)))
  )

(defun my-c-namespace-indent (langelem)
  "Used with c-set-offset, indents namespace scope elements 2 spaces
from the namespace declaration iff the open brace sits on a line by itself."
  (save-excursion
    (if (progn (goto-char (cdr langelem))
               (setq column (current-column))
               (end-of-line)
               (while (and (search-backward "{" nil t)
                           (assoc 'incomment (c-guess-basic-syntax))))
               (skip-chars-backward " \t")
               (bolp))
        2)))





;; Add 2 spaces of indentation when the open brace is on a line by itself
;;(c-set-offset 'innamespace 'my-c-namespace-indent)

;; indent solo opening braces to the same indentation as the line on
;; which the namespace starts
;;(c-set-offset 'namespace-open 'my-c-namespace-open-indent)

;; indent access labels public/private/protected by 1 space, as in 'M'. I
;; kinda like that.
;;(c-set-offset 'access-label -3)

(add-hook 'c-mode-common-hook 'turn-on-auto-fill)
(add-hook 'c++-mode-common-hook ' turn-on-auto-fill)


;; C
(add-hook 'c-mode-hook (function (lambda()
                  (c-set-style "bsd")
                  (setq c-basic-offset 4)
                  (setq indent-tabs-mode nil)
                  )
                )
     )

;; C++
(add-hook 'c++-mode-hook (function (lambda()
                    (c-set-style "bsd")
		    (c-set-offset 'innamespace 'my-c-namespace-indent)
		    (c-set-offset 'namespace-open 'my-c-namespace-open-indent)
		    (c-set-offset 'access-label -3)
                    (setq c-basic-offset 4)
                    (setq indent-tabs-mode nil)
                    )
				   
                  )
     )


;;
;; set up flex-mode
;(autoload 'flex-mode "flex")
;(add-to-list 'auto-mode-alist '("\\.l$" . flex-mode))

;; set up bison-mode
;(autoload 'bison-mode "bison")
;(add-to-list 'auto-mode-alist '("\\.y$" . bison-mode))

;; set up graphviz mode
(autoload 'graphviz-mode "graphviz")
(add-to-list 'auto-mode-alist '("\\.dot$" . graphviz-mode))

;; set up objective c mode
;;(autoload 'objc-mode "Objective C")
;;(add-to-list 'auto-mode-list '("\\.m$" . objc-mode))

;; indentation (for bison)
(setq bison-rule-separator-column 4)
(setq bison-rule-enumeration-column 6)
(setq bison-decl-type-column 7)
(setq bison-decl-token-column 16)


;;
;; scons files
(add-to-list 'auto-mode-alist '("sconstruct" . python-mode))
(add-to-list 'auto-mode-alist '("sconscript" . python-mode))
(add-to-list 'auto-mode-alist '("SConscript" . python-mode))
(add-to-list 'auto-mode-alist '("SConstruct" . python-mode))

;; If we're in a SCons build tree, set the compile-command correctly
;; The cond can be extended for other build system files, too
(add-hook 'c-mode-common-hook
	  (lambda ()
	    (cond ((or (file-exists-p "sconstruct") (file-exists-p "sconscript"))
		   (set (make-local-variable 'compile-command)
			"scons -D")))))


;;; generate a simple scons file
;(define-skeleton make-scons
;  "A skeleton for scons sconstruct file"
;  nil
;  '(setq v1(file-name-nondirectory buffer-file-name))
;  "#\n"
;  "# " (file-name-nondirectory buffer-file-name) ?\n
;  "#\n\n"
;  "# create build environment \n"
;  "env = Environment() \n\n"
;  "# configuration\n"
;  "config = env.Configure()\n\n"
;  "env = config.Finish()\n\n"
;  "# source files\n"
;  "SOURCES = Split(\"\"\" file1.cpp \"\"\")\n\n"  
;  "# compiler flags\n"
;  "#env.Append(LIBS=['lib'])\n"
;  "env.Append(CCFLAGS = ['-g', '-Wall', '-Wextra', '-D_GLIBCXX_DEBUG'])\n\n"
;  "# build target\n"
;  "executable = env.Program(target='program', source=SOURCES)\n\n"
;  "#unit = SConscript('test/sconscript', duplicate=0)\n"
;  "#env.AddPostAction(executable, './program')\n"
;  "# End of File\n"
;  )

;; generate a simple scons file for C++
(define-skeleton make-scons
  "A skeleton for scons sconstruct file (specific for C++)"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
  "#\n"
  "# " (file-name-nondirectory buffer-file-name) " file for " (current-dir) ?\n
  "#\n\n"
  "Help(\"\"\" usage: scons -Q release=1 for release builds \"\"\")\n"
  "# create build environment \n"
  "env = Environment() \n\n"
  "# configuration\n"
  "config = env.Configure()\n\n"
  "env = config.Finish()\n\n"
  "# source files\n"
  "SOURCES = Split(\"\"\" main.cpp \"\"\")\n\n"  
  "# compiler flags\n"
  "#env.ParseCofig('xxx-config --include --libs')\n"
  "#env.Append(LIBS=['lib'])\n\n"
  "# debug or release\n"
  "release = ARGUMENTS.get('release', 0)\n"
  "if int(release):\n"
  "    env.Append(CCFLAGS = ['-Wall', '-Wextra', '-pedantic', #\n"
  "                          '-Wstrict-aliasing',             #\n"
  "                          '-Wstring-aliasing=2',           #\n"
  "                          '-O2',                           # optimization\n"
  "                          '-j2',                           # dual core 4\n"
  "                          '-pipe',                         # use pipes instead of intermediat files\n"
  "                          '-fomit-frame-pointer',          # don't frame pointer in register\n"
  "                          '-ffast-math',                   # fast math\n"
  "                          '-strength-reduce',              # strength reduction optimization\n"
  "                          '-fwhole-program'                # whole program optimization \n" 
  "                         ])\n\n"
  "    targetSuffix=''\n\n"
  "else:\n"
  "    env.Append(CCFLAGS = ['-g', '-ggdb',                   # debug\n"
  "                          '-Wall', '-Wextra', '-pedantic', # extra warnings\n"
  "                          '-Woverloaded-virtual',          # warn when a function declaration hides virtual functions from a base class\n"
  "                          '-D_GLIBCXX_DEBUG',              # STL debug\n"
  "                          '-fcheck-new',                   # check that the pointer returned by operator new is non-nu\n"
  "                          '-Wctor-dtor-privacy',           # warn when a class seems unusable\n"
  "                          '-Weffc++',                      # style guidelines from Scott Meyers' Effective C++ \n"
  "                          '-j2',                           # dual core\n"
  "                          '-Wstrict-aliasing', '-Wstrict-aliasing=2',  # strict aliasing\n"
  "                          '-DDEBUG'                        # set the DEUBG macro \n"
  "                         ])\n"
  
  "    targetSuffix='.dbg'\n\n"  
  "# build target\n"
  "executable = env.Program(target='"(current-dir)"'+targetSuffix, source=SOURCES)\n\n"
  "#unit = SConscript('test/sconscript', duplicate=0)\n"
  "#env.AddPostAction(executable, './"(current-dir)"')\n"
  "# End of File\n"
  )


;; generate a simple scons file for C99
(define-skeleton make-sconsc
  "A skeleton for scons sconstruct file (specific for C99)"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
  "#\n"
  "# " (file-name-nondirectory buffer-file-name) " file for " (current-dir) ?\n
  "#\n\n"
  "Help(\"\"\" usage: scons -Q release=1 for release builds \"\"\")\n"
  "# create build environment \n"
  "env = Environment() \n\n"
  "# configuration\n"
  "config = env.Configure()\n\n"
  "env = config.Finish()\n\n"
  "# source files\n"
  "SOURCES = Split(\"\"\" main.c \"\"\")\n\n"  
  "# compiler flags\n"
  "#env.ParseCofig('xxx-config --include --libs')\n"
  "#env.Append(LIBS=['lib'])\n\n"
  "# debug or release\n"
  "release = ARGUMENTS.get('release', 0)\n"
  "if int(release):\n"
  "    env.Append(CCFLAGS = ['-Wall', '-Wextra', '-pedantic',\n"
  "                          '-std=c99',\n"
  "                           #'-std=gnu99,'                   # additonal gnu features\n" 
  "                          '-Wstrict-aliasing', '-Wstrict-aliasing=2',\n"
  "                          '-O2',                           # optimization\n"
  "                          '-j2',                           # dual core\n"
  "                          '-pipe',                         # use pipes to send rather then itermediat files\n"
  "                          '-ffast-math',                   # fast math \n"
  "                          '-minline-all-stringops',        # inline string operations\n"
  "                          '-fomit-frame-pointer',          # don't keep frame pointer in register\n"
  "                          '-fstrength-reduce',             # strength reduction optimization\n"
  "                          '-fwhole-program'                # whole program optimization \n"  
  "                         ])\n\n"
  "    targetSuffix=''\n\n"
  "else:\n"
  "    env.Append(CCFLAGS = ['-g', '-ggdb',                   # debug\n"
  "                          '-Wall', '-Wextra', '-pedantic', # extra warnings\n"
  "                          '-j2',                           # dual core \n"
  "                          '-Wbad-function-cast',           # \n"
  "                          '-std=c99',                      # C99 \n"
  "                          #'-std=gnu99',                    # additional gnu features\n"
  "                          '-Wstrict-aliasing',  '-Wstrict-aliasing=2',  # strict aliasing\n"
  "                          '-Wshadow',                      # warn for shadowing names\n"
  "                          '-Wnonnull',                     # check for NULL parameters\n"
  "                          '-Wstrict-prototypes',           # check prototypes\n"
  "                          '-Wconversion',                  # warn on a type conversion\n"
  "                          '-Wsign-compare',                # warn when a signed value can be converted\n"
  "                          '-ftrapv',                       # runtime integer error check\n"
  "                          #'-fprofile-arcs',                # gcov \n"
  "                          #'-ftest-coverage',               # gcov \n"
  "                          '-DDEBUG'                        # set the DEUBG macro \n"
  "                         ])\n"
  "    targetSuffix='.dbg'\n\n"
  
  "# build target\n"
  "executable = env.Program(target='"(current-dir)"'+targetSuffix, source=SOURCES)\n\n"  
  "# End of File\n"
  )

;;
;; autogenerera default sconstruct-fil (with support for shared libs etc.)
;;

(define-skeleton make-scons2
  "A skeleton for scons sconstruct file"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
  "#\n"
  "# " (file-name-nondirectory buffer-file-name) ?\n
  "#\n\n"
  "# create build environment \n"
  "#BuildDir('bin', 'src')\n"
  "env = Environment() \n\n"
  "# configuration\n"
  "config = env.Configure()\n\n"
  "# additional headers\n"
  "#env.Append(CPPPATH=['/home/ulf/dev'])\n\n"
  "# additional libraries\n"
  "#env.Append(LIBPATH=['/home/ulf/dev'])\n"
  "# check for specific header files\n"
  "#HEADERS = ['header.hpp']\n"
  "#for header in HEADERS:\n"
  "#\tif not config.CheckHeader(header):\n"
  "#\t\tprint \"To compile you need\" + header + \" header\"\n"
  "#\t\tExit(1)\n\n"
  "# check for specific libs\n"
  "#LIBS = ['lib']\n"
  "#for lib in LIBS:\n"
  "#\tif not config.CheckLib(lib):\n"
  "#\t\tprint \"To compile you need lib\" + lib\n"
  "#\t\tExit(1)\n\n"
  "env = config.Finish()\n\n"
  "# source files\n"
  "SOURCES = Split(\"\"\" file1.cpp file2.cpp \"\"\")\n\n" 
  "#env.Append(LIBS=['lib'])\n\n"
  "# compiler flags\n"
  "env.Append(CCFLAGS = ['-g', '-Wall'])\n\n"
  "# build target\n"
  "env.Program(target='program', source=SOURCES)\n\n"
  "#\n"
  "# ----------------------------------------------------------------------\n"
  "# Dll or LIB\n"
  "# ----------------------------------------------------------------------\n\n"
  "# build shared library\n"
  "#SharedLibrary('plugin/xxx', ['xxx.cpp', 'xxx2.cpp'])\n"
  "# build static library\n"
  "#StaticLibrary('lib/xxxlib', ['xxx.cpp'])\n\n"
  "# ----------------------------------------------------------------------\n"
  "# Docs\n"
  "# ----------------------------------------------------------------------\n\n"
  "# generate doxygen\n"
  "#doxysrc = 'doxygen'\n"
  "#target=['doc', 'html/index.html']\n"
  "#Command(target, doxysrc, 'doxygen' $SOURCES)\n\n"
  "# ----------------------------------------------------------------------\n"
  "# Archive\n"
  "# ----------------------------------------------------------------------\n\n"
  "# archive the source code\n"
  "#env = Environment(TARFLAGS='-c -z', TARSUFFIX='.tgz')\n"
  "#env.Tar('src/src', SOURCES)\n"
  "#Zip('src', SOURCES)\n\n"
  "# End of File\n"
  )

;; create a self extracting python package (wiht help of sh)
(define-skeleton make-pyx
  "A skeleton for self extracting python files"
  nil
  "#!/bin/sh\n\n"
  "PYTHON=$(which python 2>/dev/null)\n"
  "if [ ! -x \"$PYTHON\" ] ; then\n"
  "  echo \"Error: python not found!\"\n"
  "  exit 1\n"
  "fi\n"
  "exec $PYTHON -c \""
  "# Python loader:\n"
  "#!/usr/local/bin/python \n"
  "import sys, os, zipimport\n"
  "if int(sys.version[0]) < 2:\n"
  "  print 'Python version 2.3 final or greater is required.'\n"
  "  print 'Your version is: ', sys.version\n"
  "  os._exit(1)\n"
  "z = zipimport.zipimporter(sys.argv[1])\n"
  "del sys.argv[0:1]\n"
  "exec z.get_code('extract')\n"
  "\" $0 $@\n"
  )


;;
;; creating a self extractiong file script
;; default name: builder (for bash-mode)
(add-to-list 'auto-mode-alist '("builder" . sh-mode))

(define-skeleton make-extractor
  "A skeleton for self extractiong scripts"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
  "#!/bin/sh\n\n"
  "# \n"
  "# To create a self extracting archive script, use this command:\n"
  "# cat " (file-name-nondirectory buffer-file-name) " thetarpackage.tgz > nameofthescript.sh \n"
  "#\n\n"
  "echo \"\"\n"
  "echo \"Package "  (format-time-string "%y%m%d" (current-time)) " - extractiong archive... please wait\"\n"
  "echo \"\"\n\n"
  "# uncomment if you want to create a temp directory to extract to\n"
  "#export WRKDIR=`mktemp -d /tmp/selfextract.XXXXXX`\n\n"
  "# using awk to derive the number of lines in this 'header file', since\n"
  "# the NUMERIC parameter to the 'tail' must be one more than lines in this\n"
  "# file.\n\n"
  "SKIP=`awk '/^__ARCHIVE_FOLLOWS__/ { print NR + 1; exit 0; }' $0`\n\n"
  "# take the archive and pipe it to tar\n"
  "tail +$SKIP $0 | tar xz \n\n"
  "#NOTE: some *nix system might not have GNU tar!!!\n"
  "#tail +$SKIP $0 | gzip -dc | tar x - \n\n"
  "# if you are using a temp dir use this command: \n"
  "#tail +$SKIP $0 | tar xz -C $WRKDIR\n\n"
  "# execute the installation script (if there is any)\n"
  "#PREV=`pwd`\n"
  "#cd $WRKDIR\n"
  "#./install.sh\n\n"
  "# delete the temp files\n"
  "#cd $PREV\n"
  "#rm -rf $WRKDIR\n\n"
  "exit 0\n\n"
  "__ARCHIVE_FOLLOWS__\n"
  )

(define-skeleton make-package
  "A skeleton for a script to make a package"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
  "#!/bin/sh\n\n"
  "# "  (format-time-string "%y-%m-%d" (current-time)) "\n\n"
  "# make a gzipped tar ball of all the files...\n"  
  "#tar -czvf your_archive.tgz your_install.sh your_test.cpp sconstruct\n"
  "#cat installer archive.tgz > package_"(format-time-string "%y-%m-%d" (current-time))".sh\n\n"
  "#End of File\n"
  )


  
  
(define-skeleton make-make
  "A generated 'standard' Makefile"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
  "# -------------------------------------------------------------------------------\n"
  "# " (file-name-nondirectory buffer-file-name) "\n"
  "# -------------------------------------------------------------------------------\n\n"
  "# Additional paths \n"
  "#XXX_DIR = /home/ulf/\n"
  "#XXX_LIB = $(XXX_DIR)/lib\n"
  "#XXX_HDR = $(XX_DIR)/include\n\n"
  "# C/C++ preprocessor flags\n"
  "#CPPFLAGS = -I$(XXX_HDR)\n\n"
  "# Linker flags\n"
  "#LDFLAGS = -L$(XXX_LIB)\n\n"
  "COMPILERFLAGS = -Wall -g\n"
  "CXX=g++\n\n"
  "CXXFLAGS=$(COMPILERFLAGS) -I$(XXX_HDR)\n"
  "LIBS=$(XXX_LIB)/libxxx.so $(XXX_LIB)/libxxx.so\n\n"
  "program: main.o xxx.o\n"
  "\t$(CXX) $(CXXFLAGS) -o program main.cpp xxx.cpp\n\n"  
  "# End of File\n"
  )



;;
;; generateMakefile
;;

;;needed in insert-buffer/file/dir-name functions
(defun buffer-name-not-mini ()
  "Return the name of current buffer, as a string.
If current buffer is the *mini-buffer* return name of previous-window."
       (buffer-name (if (window-minibuffer-p)
                           (if (eq (get-lru-window) (next-window))
                               (window-buffer (previous-window))
                               (window-buffer (next-window)))
                           nil)))


(define-skeleton make-lib
  "A generated 'shared lib' Makefile"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
   "# ------------------------------------------------------------------------------\n"
   "# Makefile for shared library\n"
   "# ------------------------------------------------------------------------------\n\n"
   "# \n"
   "#CFLAGS = -Wall \n"
   "CXXFLAGS = -Wall \n"
   "#CC = gcc\n"
   "CXX = g++\n\n"
   "INCL = -I/usr/include\n"
   "LIBS = -L/usr/lib\n\n"
   "PROGRAM = __mylib__\n"
   "__mylib__: file1.o file2.o file3.o\n"
   "\t$(CXX) $(CXXFLAGS) -c  $@ $^ $(LIBS)\n\n"
   "AR = ar rc\n\n"
   "\t$(AR) $@ $(LIBOBJS)\n"
   "\tranlib $@\n\n"
   "#End of File\n"
  )



(define-skeleton make-dll
  "A generated 'dll' Makefile"
  nil
  '(setq v1(file-name-nondirectory buffer-file-name))
   "# ------------------------------------------------------------------------------\n"
   "# Makefile for dll\n"
   "# ------------------------------------------------------------------------------\n\n"
   "#CC = gcc\n"
   "CXX = g++\n\n"
   "CXXFLAGS = -Wall\n\n"
   "#INCL = \n"
   "#LIBS = \n\n"
   "# The module\n"
   "MODULE = __module_name__\n"
   "__module_name__: file1.o file2.o file3.o\n"
   "\t$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS) -shared\n\n"
   "# End of File\n"
  )

(defun makeLib ()
  "Genereate skeleton Makefile for lib"
  (interactive)
  (insert
   "# \n")
  )

(defun makeC ()
  "Generate skeleton Makefile"
  (interactive)
  (insert "# ------------------------------------------------------------------------------\n"
	  "# Makefile for "
	  )
  (let* ((bfn (buffer-file-name (get-buffer (buffer-name-not-mini)))))
           (if bfn
               (insert (file-name-directory bfn) "\n")))
  (insert
   "# ------------------------------------------------------------------------------\n"
   "# (C) Copyright " (user-full-name) " " (format-time-string "%Y" (current-time)) ".\n"
   "# \n\n"
   "# GCC settings \n"
   "#CC += gcc \n"
   "CXX += g++ \n\n"
   "# Paths\n"
   "# -I<include dir> for headers in a nonstandard directory\n"
   "# -L<lib dir> for libraries in a nonstandard directory\n"
   "#INCL := -I/usr/include\n"
   "#LIBS := -L/usr/lib\n\n"
   "# X11 and GL paths \n"
   "#INCL += -I/usr/X11R6/include/GL\n"
   "#LIBS += -L/usr/lib -L/usr/X11R6/lib\n\n"
   "# GLEW paths \n"
   "#INCL += -I/home/ulf/dev/glew/include\n"
   "#LIBS += -L/home/ulf/dev/glew/lib\n\n"
   "#INCL += -I/home/ulf/dev/linux_sdk/inc\n"
   "#LIBS += -L/home/ulf/dev/linux_sdk/LIBS\n\n"
   "# NVIDIA SDK paths\n"
   "#INCL += -I/home/ulf/nvsg_sdk/inc\n"
   "#LIBS += \n\n"
   "# LUA paths \n"
   "#LUA_DIR = /home/ulf/dev/lua-5.0.2\n"
   "#LUA_LIB = $(LUA_DIR)/lib\n"
   "#LUA_HDR = $(LUA_DIR)/include\n"
   "#INCL += $(LUA_HDR)\n"
   "#LIBS += $(LUA_LIB)/liblua.so $(LUA_LIB)/liblualib.so\n\n"
   "# Compiler flags \n"
   "#CFLAGS = -Wall -Werror\n"
   "CXXFLAGS = -Wall -Werror\n\n"
   "# Link with the libraries...\n"
   "#LIBS += -lCg -lCgGl -lGL -lGLU -lglut -lpthread -lXmu -Xi\n\n\n"
   "# The program\n"
   "PROGRAM = folder\n\n"
   "# ---------------------------------------------------------\n"
   "# Phony targets\n"
   ".PHONY := all clean\n\n"
   "all: $(PROGRAM)\n\n"
   "clean: \n"
   "\trm -f *.o\n"
   "\trm -f *~\n\n\n"
   "# ---------------------------------------------------------\n"
   "# Real targets, if linking with dll use -ldl\n"
   "folder: file1.o file2.o file3.o\n"
   "\t$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)\n\n"
   "# General targets\n"
   "%.o: %.cpp\n"
   "\t$(CXX) $(CXXFLAGS) -o $@ -c $^ $(INCL)\n\n\n"
   "# End of File\n"
   ))
  

;;
;; dos2unix
;;

(defun dos2unix (buffer)
      "Automate M-% C-q C-m RET C-q C-j RET"	
      (interactive "*b")    
      (save-excursion	    
        (goto-char (point-mi	n))
        (while (search-forward (	string ?\C-m) nil t)
          (replace-match (string ?\C-j)	       nil t))))

;;
(defun dos-to-unix ()
  "Convert a DOS buffer to Unix format."
  (interactive)
  (beginning-of-buffer)
  (replace-string "\r\n" "\n"))


;;
;; prettify ObjectiveCaml source
;;

(defun ocaml-unicode ()
           (int       eractive)
	       (su	   bstitute	-patterns-with-unicode
	       	            (list		   	(cons	 "\\(<-\\)" 'left-arrow)
           (con	    s "\\(->\		   \)" 'right-arrow)
           (cons "\\  [^=\\    ]\\( =\\)\\[  ^=\\]" 'equal)
           (cons "\\(=	       =\\)" '			         identical)
           (cons "\\(\\!=\\)" '	     not-identical)
           (cons "\\(<>\\)" 'not-equal)
           (cons "\\(()\\)" 'nil)
           (cons "\\<\\(sqrt\\)\\>" 'square-root)
           (cons "\\(&&\\)" 'logical-and)
           (cons "\\(||\\)" 'logical-or)
           (cons "\\<\\(not\\)\\>" 'logical-neg)
           (cons "\\(>\\)\\[^=\\]" 'greater-than)
           (cons "\\(<\\)\\[^=\\]" 'less-than)
           (cons "\\(>=\\)" 'greater-than-or-equal-to)
           (cons "\\(<=\\)" 'less-than-or-equal-to)
           (cons "\\<\\(alpha\\)\\>" 'alpha)
           (cons "\\<\\(beta\\)\\>" 'beta)
           (cons "\\<\\(gamma\\)\\>" 'gamma)
           (cons "\\<\\(delta\\)\\>" 'delta)
           (cons "\\(''\\)" 'double-prime)
           (cons "\\('\\)" 'prime)
           (cons "\\<\\(List.for_all\\)\\>" 'for-all)
           (cons "\\<\\(List.exists\\)\\>" 'there-exists)
           (cons "\\<\\(List.mem\\)\\>" 'element-of)
           (cons "^ +\\(|\\)" 'double-vertical-bar))))
  
  (add-hook 'tuareg-mode-hook 'ocaml-unicode)

;; And for Haskell:
;;(haskell-font-lock-symbols t)
  (defun haskell-unicode ()
    (interactive)
    (substitute-patterns-with-unicode
     (list (cons "\\(<-\\)" 'left-arrow)
           (cons "\\(->\\)" 'right-arrow)
           (cons "\\(==\\)" 'identical)
           (cons "\\(/=\\)" 'not-identical)
           (cons "\\(()\\)" 'nil)
           (cons "\\<\\(sqrt\\)\\>" 'square-root)
           (cons "\\(&&\\)" 'logical-and)
           (cons "\\(||\\)" 'logical-or)
           (cons "\\<\\(not\\)\\>" 'logical-neg)
           (cons "\\(>\\)\\[^=\\]" 'greater-than)
           (cons "\\(<\\)\\[^=\\]" 'less-than)
           (cons "\\(>=\\)" 'greater-than-or-equal-to)
           (cons "\\(<=\\)" 'less-than-or-equal-to)
           (cons "\\<\\(alpha\\)\\>" 'alpha)
           (cons "\\<\\(beta\\)\\>" 'beta)
           (cons "\\<\\(gamma\\)\\>" 'gamma)
           (cons "\\<\\(delta\\)\\>" 'delta)
           (cons "\\(''\\)" 'double-prime)
           (cons "\\('\\)" 'prime)
           (cons "\\(!!\\)" 'double-exclamation)
           (cons "\\(\\.\\.\\)" 'horizontal-ellipsis))))
  
  (add-hook 'haskell-mode 'haskell-unicode)


;; lua mode
;;; code starts
;; (require 'lua-mode)
;; (add-to-list 'auto-mode-alist '("\\.lua\\'" . lua-mode))
 
 ; for hs-minor-mode
 (defvar lua-sexp-alist '(("then" . "end")
                         ("function" . "end")
                         ("do" . "end")))
 (defun lua-forward-sexp (&optional arg)
  "Forward to block end"
  (save-match-data
  (let ((stackheight 0)
        (regexp ""))
    (setq regexp (concat "\\(" (mapconcat 'car lua-sexp-alist "\\|")
 "\\|end\\)"))
    (re-search-forward regexp nil t arg)
    (setq stackheight 1)
    (while ( stackheight 0)
      (re-search-forward regexp nil t arg)
      (if (string= "end" (match-string 1))
          (setq stackheight (- stackheight 1))
        (setq stackheight (+ stackheight 1)))))))
 
 (add-to-list 'hs-special-modes-alist
             `(lua-mode ,(concat "\\(?:" (mapconcat 'car
 lua-sexp-alist "\\|") "\\)")
             ,(concat "\\(?:" (mapconcat 'cdr lua-sexp-alist "\\|") "\\)")
             "--"                     ; comment prefix
             lua-forward-sexp))
 
 (defun my-lua-hook()
  (interactive)
  (hs-minor-mode 1)
  ; key bindings
  (local-set-key [?\C-,] 'hs-hide-block)
  (local-set-key [?\C-.] 'hs-show-block)
 )
 (add-hook 'lua-mode-hook 'my-lua-hook)
 ;;; code ends
			 
;;
;; TANGENTMAPPNING
;;

;;; F1 - koppa till man-sidan (för det ordet markören står vid)
(global-set-key [(f1)] (lambda () (interactive) (manual-entry
(current-word) ) ) )

;;; F2 - find file
(global-set-key [f2] 'find-file)

;;; F3 - help
(global-set-key [f3] 'help-command)

;;; F4 - autogenerare filinformation och ev. inkluderingsvakter
(global-set-key [f4] 'file-info)

;;; F5 - starta gdb-debuggern
(global-set-key (quote [f5]) 'gdb)

;;; F6 - info
(global-set-key [f6] 'help-command)

;;; F7 - kompilera
(global-set-key (quote [f7]) 'compile)

(setq compilation-finish-function
      (lambda (buf str)
	(if (null (string-match ".*exited abnormally.*" str))
	    (progn
	      (run-at-time
	       "2 sec" nil 'delete-windows-on
	       (get-buffer-create "*compilation*"))
	      (message "Inga kompilerings fel... men det kan finnas varningar"))
	  (next-error)
	  )
	)
      )

;;(defun get-beg()
;;  (save-excursion
;;    (end-of-line)
;;    (point)
;;    )
;;  )

;;(defun get-end()
;;  (save-excursion
;;    (end-of-line)
;;    (point)
;;    )
;;  )


(add-hook 'write-file-hooks 'time-stamp)

(defun buffer-non-readonly ()
  "Make buffer non-readonly."
  (interactive)
  (setq buffer-read-only nil))
(global-set-key [(alt x) q] 'buffer-non-readonly)


(defun highlight-my-keyword ()
  "Highlight code documentation keyword."
  (setq font-lock-keywords
        (append font-lock-keywords
                '(("\\bFIXME\\\|\\bHACK\\\|\\bTODO"
                   (0 'font-lock-warning-face t))))))


(defun touch-buffer ()
  "Touch, to be saved, and force recompile."
  (interactive)
  (set-buffer-modified-p t))
(global-set-key [(control x) t] 'touch-buffer)

(setq user-mail-address "ulf.ejlertsson@gmail.com")
(setq user-full-name "Ulf Ejlertsson")


(defun current-dir()
  "Current directory"
  (interactive)
   ( file-name-nondirectory (directory-file-name(file-name-directory(directory-file-name buffer-file-name))) )
   )
  

;;;
;;; file-info
;;;


;; generate a simple scons file for C99
;(define-skeleton make-sconsc
;  "A skeleton for scons sconstruct file (specific for C99)"
;  nil
;  '(setq v1(file-name-nondirectory buffer-file-name))
;  "#\n"

;;(defun file-info()
  (define-skeleton file-info
 "Filinformation"
 ;(interactive)
 nil
 ;; C/C++
 (if
     (or
      (or
       (or
	(string-match "\\.ipp$" buffer-file-name)
	)
       (string-match "\\.c$" buffer-file-name)
       (string-match "\\.cpp$" buffer-file-name)
       )
      (string-match "\\.h$" buffer-file-name)
      (string-match "\\.hpp$" buffer-file-name)
      )
     (insert "// -----------------------------------------------------------------------------\n"
	     "// " (file-name-nondirectory buffer-file-name)" \n"
;;	     "// " ( file-name-nondirectory (directory-file-name(file-name-directory(directory-file-name buffer-file-name))) )"\n"	    
	     "// -----------------------------------------------------------------------------\n"
	     "// \n"
	     "// (C) Copyright " (user-full-name) " " (format-time-string "%Y" (current-time)) ".\n"
	     "// \n\n")
   )
 
 (if
     (or
      (or
       (string-match "\\.ipp$" buffer-file-name)
       )
      (string-match "\\.h$" buffer-file-name)
      (string-match "\\.hpp$" buffer-file-name)
      )
     (insert "#ifndef __"
	     (upcase
	      (current-dir) 
	      )
	     "_"
	     (upcase
	      (file-name-sans-extension
	       (file-name-nondirectory buffer-file-name)
	       )
	      )
	     "_" (upcase
		  (file-name-extension
		   (file-name-nondirectory buffer-file-name)
		   )
		  )
	     "_INCLUDED__\n"
	     "#define __"
	     (upcase
	      (current-dir)
	      )
	     "_"
	     (upcase
			   (file-name-sans-extension
			    (file-name-nondirectory buffer-file-name)
			    )
			   )
	     "_" (upcase
		  (file-name-extension
		   (file-name-nondirectory buffer-file-name)
		   )
		  )
	     "_INCLUDED__\n\n\n"
	     "#endif // !__"
	     (upcase
	      (current-dir)
	      )
	     "_"
	     (upcase
			    (file-name-sans-extension
			     (file-name-nondirectory buffer-file-name)
			     )
			    )
	     "_" (upcase
		  (file-name-extension
		   (file-name-nondirectory buffer-file-name)
		   )
		  )
	     "_INCLUDED__\n\n"
	     "/* End of File */")
   )
 
 ;; elisp
 (if (string-match "\\.el$" buffer-file-name)
     (insert ";; Mode: -*- Emacs-Lisp -*-\n"
             ";; ------------------------------------------------------------------------------\n"
             ";; " (file-name-nondirectory buffer-file-name) "\n"
             ";; ------------------------------------------------------------------------------\n"
	     ";;\n\n\n"
	     ";; End of File\n")
 )
 
 ;; python och bash
 (if (string-match "\\.py$" buffer-file-name)
     (insert "#!/usr/bin/env python \n"))
 (if (string-match "\\.sh$" buffer-file-name)
     (insert "# !/bin/bash2\n"))
 (if
     (or
      (string-match "\\.py$" buffer-file-name)
      (string-match "\\.sh$" buffer-file-name)
      )
     (insert "# ------------------------------------------------------------------------------\n"
	     "# " (file-name-nondirectory buffer-file-name) "\n"
	     "# ------------------------------------------------------------------------------\n"
	     "# \n"
	     "# (C) Copyright "(user-full-name) " " (format-time-string	"%Y" (current-time)) "\n"
	     "# \n\n\n"
	     "# End of Script\n")
   )

 ;; objective c
 (if
     (string-match "\\.m$" buffer-file-name)
     (insert "// -----------------------------------------------------------------------------\n"
	     "// " (file-name-nondirectory buffer-file-name) "\n"
	     "// -----------------------------------------------------------------------------\n"
	     "// \n\n")
   )
 
 ;; haskell och lua
 (if
     (or
      (string-match "\\.hs$" buffer-file-name)
      (string-match "\\.lua$" buffer-file-name)
      )
     (insert "-- -----------------------------------------------------------------------------\n"
	     "-- " (file-name-nondirectory buffer-file-name) "\n"
	     "-- -----------------------------------------------------------------------------\n"
	     "-- \n"
	     "-- (C) Copyright "(user-full-name) " " (format-time-string
						      "%Y" (current-time)) "\n"
						      "-- \n\n\n"
						      "-- End of Script\n")
   )
 
 ;; ml, ocaml och mli (ocaml interface)
 (if
     (or
      (string-match "\\.ml$" buffer-file-name)
      (string-match "\\.mli$" buffer-file-name)
      )
     (insert "(* -----------------------------------------------------------------------------\n"
	     " * " (file-name-nondirectory buffer-file-name) "\n"
	     " * -----------------------------------------------------------------------------\n"
	     " * \n"
	     " * (C) Copyright "(user-full-name) " " (format-time-string
						      "%Y" (current-time)) "\n"
						      " * \n"
						      " *)\n\n\n"
						      "(*  End of Script *)\n"
						      )
   )
 
 ;; yacc och lex
 (if
     (or
      (string-match "\\.l$"  buffer-file-name)
      (string-match "\\.ll$" buffer-file-name)
      (string-match "\\.y$"  buffer-file-name)
      (string-match "\\.yy$" buffer-file-name)
      )
     (insert "/* *****************************************************************************\n"
	     " * " (file-name-nondirectory buffer-file-name) "\n"
	     " * *****************************************************************************\n"
	     " *\n"
             " *\n"
             " */\n\n"
             "/* Definitions */\n"
             "%{\n\n"
	     "/*\n"
	     " * (C) Copyright "(user-full-name) " " (format-time-string
						      "%Y" (current-time)) "\n"	     
	     " */ \n\n"
             "%}\n\n"
             " \n"
             "%%  /* Grammar rules */\n\n"
             " \n"
             "%%  /* Subroutines */\n\n\n"
             "/* End of File */\n"
	     )
   )
 
 ;; tex
 (if (string-match "\\.tex$" buffer-file-name)
     (insert "% ------------------------------------------------------------------------------\n"
	     "% " (file-name-nondirectory buffer-file-name) "\n"
	     "% ------------------------------------------------------------------------------\n"
             "%\n\n"
             "\\documentclass{article}\n"
	     "\\bibliographystyle{plain}\n\n"
	     "\\usepackage[T1]{fontenc}\n"
	     "\\usepackage[swedish]{babel}\n"
	     "\\usepackage{ae}\n"
	     "\\usepackage{latexsym}\n"
	     "%\\usepackage{amssymb}\n"
	     "%\\usepackage[section]{algorithm}\n"
	     "%\\usepackage{algorithmic}\n"
	     "% PostScript fonts in text and equations	\n"
	     "%\\usepackage{pslatex}\n\n"
	     "\\usepackage{textcomp} \n"
	     "\\usepackage [utf8] {inputenc} \n\n"
	     "\\usepackage[dvips]{graphicx}\n\n"
	     "\\usepackage{fancyhdr}\n\n"
	     "\\fancyfoot[C]{\\footnotesize{\\title}} 	% Delete current footer settings \n"
	     "\\renewcommand{\\sectionmark}[1]{         % Lower case Section marker style \n"
	     "\\markright{\\thesection.\\ #1}}           %		\n"
	     "\\fancyhead[LE,RO]{\\bfseries\\thepage}    % Page number (boldface) in left on even \n"
	     "                                        % pages and right on odd pages \n"
	     "\\fancyhead[RE]{\\bfseries\\leftmark}      % Chapter in the right on even pages \n"
	     "\\fancyhead[LO]{\\bfseries\\rightmark}     % Section in the left on odd pages \n"
	     "\\renewcommand{\\headrulewidth}{0.3pt}    % Width of head rule \n"
	     "\\newcommand{\\lb}{[\\![}                  % left double bracket\n"
	     "\\newcommand{\\rb}{]\\!]}                  % right double bracket\n\n"
	     "\\title{Title \\\\ \\small{subtitle}}\n"
	     "\\author{Ulf Ejlertsson\\footnote{ulf@linuxmail.org}}\n"
	     "\\date{}\n\n"
	     "%\\pagenumbering{roman}    % \n"
	     "%\\fancypagestyle{empty}   \n\n"
	     "%\\raggedright\n"
	     "%\\tableofcontents \n"
	     "%\\listoftables \n"
	     "%\\listoffigures \n\n"
	     "\\begin{document}  \n\n"
	     "\\maketitle\n\n"
	     "%\\input{graphviz}\n\n"
	     "% fixar till sÃƒÂ¥ att dokumentet blir snyggt\n"
	     "%\\pagestyle{fancy} % Sets fancy header and footer \n"
	     "%\\pagenumbering{arabic} \setcounter{page}{1} \n\n"
	     "%\\begin{abstract} \n"
	     "%\\end{abstract}\n\n\n"
	     "%\\section{XXX}\n\n"
	     "%\\bibliography{books}\n"
	     "%\\bibliographystyle{style}\n\n"
	     "%\\begin{thebibliography}{99}\n"
	     "% \\bibitem{CAML} Inrias  sida om Caml, \\href{http://caml.inria.fr/}{http://caml.inria.fr}\n"
	     "%\\end{thebibliography} \n\n"
	     "\\end{document}\n\n"
	     "% End of File \n"
	     )
   )

  ;; cg
  (if (string-match "\\.cg$" buffer-file-name)
      (insert "// -----------------------------------------------------------------------------\n"
              "// " (file-name-nondirectory buffer-file-name) "\n"
              "// -----------------------------------------------------------------------------\n"
              "// nVidia's C for Graphics (CG) \n"
              "// link with -lCg -lCgGL -lpthread (Linux needs pthread for some reason)\n"
              "// \n\n\n"
              "/* End of File */\n"
      )
  )

  (if (string-match "\\.plan$" buffer-file-name)
      (insert "**\n"
	      "** " (file-name-nondirectory buffer-file-name) "\n"
	      "**\n"
	      "** " (buffer-file-name) "\n"
	      "** Time-stamp: <"(format-time-string "%Y %m %d" (current-time))"> \n"
	      "**\n\n\n"
	      "** End of File\n")
    )

  ;; asm / s
   (if
        (or
      (string-match "\\.s$"  buffer-file-name)
      (string-match "\\.asm$" buffer-file-name)
      )
      (insert "#  -----------------------------------------------------------------------------\n"
	      "#  " (file-name-nondirectory buffer-file-name) "\n"
	      "#  -----------------------------------------------------------------------------\n"
	      "# \n\n"
	      "# initialized data \n"
	      ".section .data \n\n"
	      "# uninitialized data\n"
	      ".section .bss \n\n"
	      "# instruction code\n"
	      ".section .text \n"
	      ".globl _start \n"
	      "_start: \n"
	      "# work around for gdb bugg\n"
	      "#nop\n\n"
	      "# To compile with GCC \n"
	      "#.globl main \n"
	      "#main: \n"
	      "\n\n"
	      "# End of File\n")
    )
 )

 (define-skeleton file-info2
 "Filinformation"
 ;(interactive)
 nil
 ;; C/C++
 (if
     (or
      (or
       (or
	(string-match "\\.ipp$" buffer-file-name)
	)
       (string-match "\\.c$" buffer-file-name)
       (string-match "\\.cpp$" buffer-file-name)
       )
      (string-match "\\.h$" buffer-file-name)
      (string-match "\\.hpp$" buffer-file-name)
      )
     (insert "// -----------------------------------------------------------------------------\n"
	     "// " (file-name-nondirectory buffer-file-name)" \n"
;;	     "// " ( file-name-nondirectory (directory-file-name(file-name-directory(directory-file-name buffer-file-name))) )"\n"	    
	     "// -----------------------------------------------------------------------------\n"
	     "// \n"
	     "// (C) Copyright " (user-full-name) " " (format-time-string "%Y" (current-time)) ".\n"
	     "// \n\n")
   )
 
 (if
     (or
      (or
       (string-match "\\.ipp$" buffer-file-name)
       )
      (string-match "\\.h$" buffer-file-name)
      (string-match "\\.hpp$" buffer-file-name)
      )
     (insert "#ifndef __"
	     (upcase
	      (current-dir) 
	      )
	     "_"
	     (upcase
	      (file-name-sans-extension
	       (file-name-nondirectory buffer-file-name)
	       )
	      )
	     "_" (upcase
		  (file-name-extension
		   (file-name-nondirectory buffer-file-name)
		   )
		  )
	     "_INCLUDED__\n"
	     "#define __"
	     (upcase
	      (current-dir)
	      )
	     "_"
	     (upcase
			   (file-name-sans-extension
			    (file-name-nondirectory buffer-file-name)
			    )
			   )
	     "_" (upcase
		  (file-name-extension
		   (file-name-nondirectory buffer-file-name)
		   )
		  )
	     "_INCLUDED__\n\n"
	     "#if (defined _MSC_VER) && (_MSC_VER >= 1200)\n"
	     "#  pragma once\n"
	     "#endif\n\n"
	     "#define "(upcase (current-dir)) "_NAMESPACE_BEGIN\n\n\n"
	     "#define "(upcase (current-dir)) "_NAMESPACE_END\n\n"
	     "#endif // !__"
	     (upcase
	      (current-dir)
	      )
	     "_"
	     (upcase
			    (file-name-sans-extension
			     (file-name-nondirectory buffer-file-name)
			     )
			    )
	     "_" (upcase
		  (file-name-extension
		   (file-name-nondirectory buffer-file-name)
		   )
		  )
	     "_INCLUDED__\n\n"
	     "/* End of File */")
   )
 )

;; Switches between source/header files
(defun toggle-source-header()
  "Switches to the source buffer if currently in the header buffer and vice versa."
  (interactive)
  (let ((buf (current-buffer))
        (name (file-name-nondirectory (buffer-file-name)))
        file
        offs)
    (setq offs (string-match c++-header-ext-regexp name))
    (if offs
        (let ((lst c++-source-extension-list)
              (ok nil)
              ext)
          (setq file (substring name 0 offs))
          (while (and lst (not ok))
            (setq ext (car lst))
            (if (file-exists-p (concat file "." ext))
                  (setq ok t))
            (setq lst (cdr lst)))
          (if ok
              (find-file (concat file "." ext))))
      (let ()
        (setq offs (string-match c++-source-ext-regexp name))
        (if offs
            (let ((lst c++-header-extension-list)
                  (ok nil)
                  ext)
              (setq file (substring name 0 offs))
              (while (and lst (not ok))
                (setq ext (car lst))
                (if (file-exists-p (concat file "." ext))
                    (setq ok t))
                (setq lst (cdr lst)))
              (if ok
                  (find-file (concat file "." ext)))))))))


(defun make-makefile()
  "Creates the Makefile from the .pro project file"
  (interactive)
  (let ((project (project-main)))
    (shell-command (concat "tmake -o Makefile "
                           (file-name-nondirectory (buffer-file-name project))))))




; From "Linux kernel coding style" by Linus Torvalds:
; This will define the M-x linux-c-mode command.  When hacking on a
; module, if you put the string -*- linux-c -*- somewhere on the first
; two lines, this mode will be automatically invoked.
(defun linux-c-mode ()
  "C mode with adjusted defaults for use with the Linux kernel."
  (interactive)
  (c-mode)
  (setq c-indent-level 8)
  (setq c-brace-imaginary-offset 0)
  (setq c-brace-offset -8)
  (setq c-argdecl-indent 8)
  (setq c-label-offset -8)
  (setq c-continued-statement-offset 8)
  (setq indent-tabs-mode nil)
  (setq tab-width 8))

; More from Linus Torvalds for Linux kernel hacking: 
; Uncomment the following if you want to have linux-c-mode switched on
; automagically when you edit source files under /usr/src/linux.
(setq auto-mode-alist (cons '("/usr/src/linux.*/.*\\.[ch]$" . linux-c-mode)
                       auto-mode-alist))






;;
;; lisp
;;

;(defun my-lisp-mode-hook ()
;  (my-code-mode-hook)
;  )
;(add-hook 'lisp-mode-hook 'my-lisp-mode-hook)
;(add-hook 'emacs-lisp-mode-hook 'my-lisp-mode-hook)
;(add-hook 'lisp-interaction-mode-hook 'my-lisp-mode-hook)

;(defun my-unedebug-defun ()
;  "I can't believe emacs doesn't give you a way to do this!!"
;  (interactive t)
;  (eval-expression (edebug-read-top-level-form)))

;;

;;; --- Scheme mode hook ---
;;(add-hook 'scheme-mode-hook
;;	  (function (lambda () (balance-mode t))))

;;; --- Open-GL mode hook ---
(add-hook 'OpenGL-minor-mode-hook 
	  '(lambda ()
	     (define-key OpenGL-minor-mode-map "\e\C-i" 'OpenGL-complete-symbol)
	     (define-key OpenGL-minor-mode-map "\C-ho"  'OpenGL-describe-symbol-briefly)
	     (define-key OpenGL-minor-mode-map "\C-cl"  'OpenGL-new-list)
	     (define-key OpenGL-minor-mode-map "\C-co"  'OpenGL-new-object)))

;; Hack fÃ¶r att fÃ¥ lite styrsel pÃ¥ bison- och flex-filerna...
(defun bison-flex-mode ()
  "Home made bison- and flex-mode."
  (interactive)
  (c-mode)
  (setq c-indent-level 4)
  (setq c-brace-imaginary-offset 0)
  (setq c-brace-offset -8)
  (setq c-argdecl-indent 8)
  (setq c-label-offset -8)
  (setq c-continued-statement-offset 8)
  (setq indent-tabs-mode nil)
  (setq tab-width 4))

(autoload 'bison-flex-mode "bisonflex")
(add-to-list 'auto-mode-alist '("\\.l$" . bison-flex-mode))
(add-to-list 'auto-mode-alist '("\\.y$" . bison-flex-mode))

;; set up flex-mode
;;(autoload 'flex-mode "flex")
;;(add-to-list 'auto-mode-alist '("\\.l$" . flex-mode))

;; set up bison-mode
;;(autoload 'bison-mode "bison")
;;(add-to-list 'auto-mode-alist '("\\.y$" . bison-mode))

;; fix för avsaknaden av flex- och bison-mode
;;(setq auto-mode-alist '(
;;  ("\\.el\\'"    . emacs-lisp-mode)
;;  ("\\.emacs\\'" . emacs-lisp-mode)
;;  ("\\.y\\'"	 . c-mode)
;;  ("\\.l\\'"	 . c-mode)
;;  ("\\.c\\'"     . c-mode)
;;  ("\\.h\\'"     . c-mode)
;;  ("\\.tex\\'"   . LaTeX-mode)
;;  ("\\.sty\\'"   . LaTeX-mode)
;;  ("\\.bbl\\'"   . LaTeX-mode)
;;  ("\\.bib\\'"   . bibtex-mode)
;;  ("\\.pl\\'"    . perl-mode)
;;  ("\\.awk\\'"   . awk-mode)
;;  ("\\.html\\'"  . html-mode)
;;  ("\\.cpp\\'"   . cpp-mode)
;;  ("\\.hpp\\'"   . cpp-mode)
;;))



;;; --- Bison mode ---
;(autoload 'bison-mode "bison-mode"
;  "Major mode for Bison files" t)
;(setq auto-mode-alist (cons '("\\.y$" . bison-mode) auto-mode-alist))

;;; --- Flex Mode ---
;(autoload 'flex-mode "flex-mode"
;  "Major mode for Flex files" t)
;(setq auto-mode-alist (cons '("\\.l$" . flex-mode) auto-mode-alist))

;;; --- Prolog mode ---
(autoload 'run-prolog "prolog" "Start a Prolog sub-process." t)
(autoload 'prolog-mode "prolog" "Major mode for editing Prolog programs." t)
(autoload 'mercury-mode "prolog" "Major mode for editing Mercury programs." t)
(setq prolog-system 'sicstus)
(setq auto-mode-alist (append '(("\\.pl$" . prolog-mode)
                                ("\\.m$" . mercury-mode))
			      auto-mode-alist))

;;; --- Scheme mode ---
;;(autoload 'scheme-mode "iuscheme" 
;;  "Major mode for Scheme." t)   
;;(autoload 'run-scheme "iuscheme" 
;;  "Switch to interactive Scheme buffer." t)
;;(autoload 'run-alt-scheme "iuscheme" 
;;  "Switch to interactive alternative Scheme buffer." t)
;;(autoload 'scheme-mode "cmuscheme" 
;;  "Major mode for Scheme." t)
;;(autoload 'run-scheme "cmuscheme" 
;;  "Switch to interactive Scheme buffer." t)
;;(autoload 'run-alt-scheme "cmuscheme" 
;;  "Switch to interactive alternative Scheme buffer." t)
;;(setq auto-mode-alist (cons '("\\.ss$" . scheme-mode) auto-mode-alist))
;;(require 'balance-mode)

;;; --- Tcl/Tk mode ---
(autoload 'tcl-mode "tcl" "Tcl mode." t)
(autoload 'inferior-tcl "tcl" "Run inferior Tcl process." t)
(autoload 'tcl-help-on-word "tcl" "Help on Tcl commands" t)
(setq auto-mode-alist (append '(("\\.tcl$" . tcl-mode)) auto-mode-alist))
(setq tcl-help-directory-list '("/usr/local/lib/tclx/help"))

;;; --- Open-GL minor mode ---
(autoload 'OpenGL-minor-mode "OpenGL" "OpenGL editing utilities." t)

;; Command to auto load the OpenGLSL mode for files ending with .vert and .frag\
	(autoload 'glsl-mode "glsl-mode" nil t)
	(add-to-list 'auto-mode-alist '("\\.vert\\'" . glsl-mode))
	(add-to-list 'auto-mode-alist '("\\.frag\\'" . glsl-mode))

;; load Cg mode
;	(autoload 'cg-mode "cg-mode" nil t)
;	(add-to-list 'auto-mode-alist '("\\.cg\\'" . cg-mode))

(add-to-list 'auto-mode-alist '("\\.cg" . c-mode))

;; set up graphviz mode
(autoload 'graphviz-mode "graphviz")
(add-to-list 'auto-mode-alist '("\\.dot$" . graphviz-mode))

;; Objective C
(add-to-list 'auto-mode-alist '("\\.m" . objc-mode))

;; FIXME
;; indentation
(setq tab-width 4)
(setq haskell-indent-offset 4)
(setq indent-tabs-mode nil)
(setq bison-rule-separator-column 4)
(setq bison-rule-enumeration-column 6)
(setq bison-decl-type-column 7)
(setq bison-decl-token-column 16)

(setq minibuffer-max-depth nil)
