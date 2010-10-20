;;
;; -*- Emacs-Lisp -*-
;; ------------------------------------------------------------------------
;; init.el
;; -----------------------------------------------------------------------

(setq user-full-name "Ulf Ejlertsson")

;; Prevent the start screen from showing up
(setq inhibit-startup-message t)

;; y istället för yes
(fset 'yes-or-no-p 'y-or-n-p)

;; Sets the time format to 24hr format
(setq display-time-24hr-format t)

;;; Displays time, date and system load in the mode-line
(display-time)

;;; Displays the column number in the mode-line
;;(display-column-mode t)
;;; Displays the line number in the mode-line
(line-number-mode t)

;;; matchande parenteser
;;(paren-set-mode 'paren)

;;; kompileringsfönster
(setq compilation-window-height 10)

;;; GUD mode
(defvar gud-overlay
  (let* ((ov (make-overlay (point-min) (point-min))))
    (overlay-put ov 'face 'secondary-selection)
    ov)
  "Overlay variable for GUD highlighting.")

(defadvice gud-display-line (after my-gud-highlight act)
  "Highlight current line."
  (let* ((ov gud-overlay)
	 (bf (gud-find-file true-file)))
    (save-excursion
      (set-buffer bf)
      (move-overlay ov (line-beginning-position) (line-end-position)
		    (current-buffer)))))


;;; inget pip
(setq visible-bell t)

;;; alltid newline
(setq require-final-newline t)

;;; stanna vid sista raden
(setq next-line-add-newlines nil)

;; scrolla rad för rad istället för stora steg
;;(setq scroll-step 1)
(set-variable 'scroll-conservatively 5)

;;; indentera automatiskt, genom att byta plats på RET och LF
(setq foo (global-key-binding "\C-m"))
(global-set-key "\C-m" (global-key-binding "\C-j"))
(global-set-key "\C-j" foo)

;;; Öppna oidentifierade filer i textläge
(setq default-major-mode 'text-mode)

;;; Always do syntax highlighting
(global-font-lock-mode 1)

;;; Also highlight parens
(setq show-paren-delay 0
      show-paren-style 'parenthesis)
(show-paren-mode 1)

;;;
;; Add /Users/ulf/bin to the emacs shell path
(add-to-list 'exec-path "/Users/ulf/bin")

;; org mode
(add-to-list 'load-path "/Users/ulf/.emacs.d/elisp/org-7.01h/lisp")
(require 'org-install)


(add-to-list 'auto-mode-alist '("\\.org$" . org-mode))
(define-key global-map "\C-cl" 'org-store-link)
(define-key global-map "\C-ca" 'org-agenda)
(setq org-export-with-LaTeX-fragments t)
(setq org-log-done t)

;; Mobile org / Dropbox
;; Set to the location of your Org files on your local system
(setq org-directory "~/org")
;; Set to the name of the file where new notes will be stored
(setq org-mobile-inbox-for-pull "~/org/flagged.org")
;; Set to <your Dropbox root directory>/MobileOrg.
(setq org-mobile-directory "~/Dropbox/MobileOrg")

;; CEDET
(load-file "/Applications/Emacs.app/Contents/Resources/site-lisp/cedet/common/cedet.el")
;/opt/local/var/macports/build/_opt_local_var_macports_sources_rsync.macports.org_release_ports_editors_emacs/work/emacs-23.2/lisp/cedet
(global-ede-mode 1)                      ; Enable the Project management system
(semantic-load-enable-code-helpers)      ; Enable prototype help and smart completion 
;(global-srecode-minor-mode 1)            ; Enable template insertion menu


;; Clojure/SLIME


;; erlang
(add-to-list 'load-path "/opt/local/lib/erlang/lib/tools-2.6.6/emacs")
(require 'erlang-start)

(add-to-list 'auto-mode-alist '("\\.erl?$" . erlang-mode))
(add-to-list 'auto-mode-alist '("\\.hrl?$" . erlang-mode))

(setq erlang-root-dir "/opt/local/lib/erlang")
(add-to-list 'exec-path "/opt/local/lib/erlang/bin")
(setq erlang-man-root-dir "/opt/local/lib/erlang/man")

;; 
(defun my-erlang-mode-hook ()
        ;; when starting an Erlang shell in Emacs, default in the node name
        (setq inferior-erlang-machine-options '("-sname" "emacs"))
        ;; add Erlang functions to an imenu menu
        (imenu-add-to-menubar "imenu")
        ;; customize keys
        (local-set-key [return] 'newline-and-indent)
        )
;; Some Erlang customizations
(add-hook 'erlang-mode-hook 'my-erlang-mode-hook)


;; Scala
;;(defun me-turn-off-indent-tabs-mode ()
;;  (setq indent-tabs-mode nil))
;;(add-hook 'scala-mode-hook 'me-turn-off-indent-tabs-mode)

;;(let ((path "/usr/local/share/emacs/site-lisp/scala"))
;;  (setq load-path (cons path load-path))
;;  (load "scala-mode-auto.el"))

;;(defun scala-turnoff-indent-tabs-mode ()
;;  (setq indent-tabs-mode nil))

;; scala mode hooks
;;(add-hook 'scala-mode-hook 'scala-turnoff-indent-tabs-mode)


;; Hooks
(add-hook 'c-mode-hook        'flyspell-prog-mode 1)
(add-hook 'c++-mode-hook      'flyspell-prog-mode 1)
(add-hook 'makefile-mode-hook 'flyspell-prog-mode 1)
(add-hook 'python-mode-hook   'flyspell-prog-mode 1)
(add-hook 'sh-mode-hook       'flyspell-prog-mode 1)

;; Objective C
(autoload 'objc-mode "cc-mode" "Objective-C Editing Mode" t)

;; C/C++
(require 'cc-mode)

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

;; Slime (for lisp and clojure)
(setq inferior-lisp-program "/opt/local/bin/sbcl") ; your Lisp system
     (add-to-list 'load-path "~/hacking/lisp/slime/")  ; your SLIME directory
     (require 'slime)
     (slime-setup)



;; ------------------------------------------------------------------------------------
;;
;; scons files
(add-to-list 'auto-mode-alist '("sconstruct" . python-mode))
(add-to-list 'auto-mode-alist '("sconscript" . python-mode))
(add-to-list 'auto-mode-alist '("SConstruct" . python-mode))

;; If we're in a SCons build tree, set the compile-command correctly
;; The cond can be extended for other build system files, too
(add-hook 'c-mode-common-hook
	    (lambda ()
	          (cond ((or (file-exists-p "sconstruct") (file-exists-p "SConscript"))
			    (set (make-local-variable 'compile-command)
				 "scons -D")))))

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
					    "    env.Append(CCFLAGS = ['-Wall', '-Wextra', '-pedantic',\n"
					      "                          '-Wstrict-aliasing', \n"
					        "                          '-Wstring-aliasing=2', \n"
						  "                          '-O2',                           # optimization\n"
						    "                          '-march=pentium4',               # pentium 4\n"
						      "                          '-pipe', \n"
						        "                          '-fomit-frame-pointer', \n"
							  "                          '-fwhole-program'                # whole program optimization \n"
							    "                         ])\n\n"
							      "    targetSuffix=''\n\n"
							        "else:\n"
								  "    env.Append(CCFLAGS = ['-g', '-ggdb',                   # debug\n"
								    "                          '-Wall', '-Wextra', '-pedantic', # extra warnings\n"
								      "                          '-D_GLIBCXX_DEBUG',              # \n"
								        "                          '-fcheck-new',                   # \n"
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
;; -----------------------------------------------------------------------------------

;; And for Haskell:

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

;; -----------------------------------------------------------------
;;
;; TANGENTMAPPNING -  funkar inte i OS X
;;

;;; F1 - koppla till man-sidan (för det ordet markören står vid)
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


(defvar c++-file-exts [("h" "hpp" "hh")  ("inl") ("c" "cpp" "cc")])

(defun find-alternate-file (base-filename possible-exts)
  "Try to find a filename starting with BASE-FILENAME with any of the extensions in POSSIBLE-EXTS"
  (let ((index 0) (result nil) (candidate nil))
    (while (and (not result) possible-exts)
      (setq candidate (concat base-filename "." (car possible-exts)))
      (when (file-exists-p candidate)
 (setq result candidate))
      (setq possible-exts (cdr possible-exts)))
    result))

(defun cycle-source/header ()
  "Cycle between header, aux (inline) and source files."
  (interactive)
  (let* ((buf (current-buffer))
  (buffer-name (buffer-file-name))
  (base-name (file-name-sans-extension buffer-name))
  (extension (file-name-extension buffer-name))
  (ext-set-count (length c++-file-exts))
  result
  current-index
  initial-index)
    (dotimes (i ext-set-count)
      (when (member extension (aref c++-file-exts i))
 (setq initial-index i)))
    (if (not (null initial-index))
 (progn
   (setq current-index (% (+ initial-index 1) ext-set-count))
   (while (and (not result) (/= current-index initial-index))
     (setq result (find-alternate-file base-name (aref c++-file-exts current-index)))
     (setq current-index (% (+ current-index 1) ext-set-count)))
   (when result
     (find-file result)))
      (progn
 (error "unsupported extension: %s" extension)))))

(global-set-key [f9] 'cycle-source/header)


;;;
;;; file-info
;;;

(defun file-info()
 "Filinformation"
 (interactive)
 ;; C/C++
 (if
     (or
      (or
       (string-match "\\.c$" buffer-file-name)
       (string-match "\\.cpp$" buffer-file-name)
       )
      (string-match "\\.h$" buffer-file-name)
      (string-match "\\.hpp$" buffer-file-name)
      )
     (insert "// -----------------------------------------------------------------------------\n"
	     "// " (file-name-nondirectory buffer-file-name)" \n"
	     ;;     "// " ( file-name-nondirectory (directory-file-name(file-name-directory(directory-file-name buffer-file-name))) )"\n"    
	     "// -----------------------------------------------------------------------------\n"
	     "// \n"
	     "// (C) Copyright " (user-full-name) " " (format-time-string "%Y" (current-time)) ".\n"
	     "// \n\n")
   )
 
 (if
     (or
      (string-match "\\.h$" buffer-file-name)
      (string-match "\\.hpp$" buffer-file-name)
      )
     (insert "#ifndef __"
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
 
 ;; python och bash
 (if (string-match "\\.py$" buffer-file-name)
     (insert "#!/usr/bin/env python \n"))
 (if (string-match "\\.sh$" buffer-file-name)
     (insert "# !/bin/bash\n"))
 (if
     (or
      (string-match "\\.py$" buffer-file-name)
      (string-match "\\.sh$" buffer-file-name)
      )
     (insert "# ------------------------------------------------------------------------------\n"
	     "# " (file-name-nondirectory buffer-file-name) "\n"
	     "# ------------------------------------------------------------------------------\n"
	     "# \n"
	     "# (C) Copyright "(user-full-name) " " (format-time-string"%Y" (current-time)) "\n"
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

 ;; erlang
 (if
     (or
      (string-match "\\.erl" buffer-file-name)
      (string-match "\\.hrl" buffer-file-name)
      )
     (insert "%% ------------------------------------------------------------------------------\n"
	     "%% " (file-name-nondirectory buffer-file-name) "\n"
	     "%% ------------------------------------------------------------------------------\n"
	     "%% \n"
	     "%% (C) Copyright " (user-full-name) " " (format-time-string "%Y" (current-time)) "\n"
						      "%% \n\n"
						      )
   )
   (if
       (string-match "\\.erl" buffer-file-name)
       (insert 
	"-module(" (file-name-sans-extension (file-name-nondirectory buffer-file-name)) ").\n\n"
	"%% Module info.\n"
	"-author({ulf, ejlertsson}).\n"
	"-vsn(\"0.1.0\").\n\n"			     
	"%% Import.\n"
	"-include_lib(\"eunit/include/eunit.hrl\").   %% Unit tests\n\n"
	"%% Export.\n"
	"%-export([]).\n\n"						  
	"%% End of File\n")
     )
 )
 


;;; This was installed by package-install.el.
;;; This provides support for the package system and
;;; interfacing with ELPA, the package archive.
;;; Move this code earlier if you want to reference
;;; packages in your .emacs.
(when
    (load
     (expand-file-name "~/.emacs.d/elpa/package.el"))
  (package-initialize))
