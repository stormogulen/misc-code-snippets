(custom-set-variables)

; Syntax highlighting. Light background.
; Insert this in custom.el. Then restart XEmacs.

(custom-set-faces
 '(default ((t (:foreground "#000000" :background "#FFFFFF" :size "11pt" :family "Terminal"))) t)
 '(cperl-array-face ((t (:foreground "orangered" :bold t))))
 '(cperl-hash-face ((t (:foreground "Red" :bold t))))
 '(cperl-nonoverridable-face ((t (:foreground "orange" :bold t))))
 '(custom-button-face ((t (:bold t :foreground "#3fdfcf"))))
 '(custom-comment-face ((((class grayscale color) (background light)) (:foreground "     black"))))
 '(custom-group-tag-face ((t (:underline t :foreground "blue"))))
 '(custom-saved-face ((t (:underline t :foreground "orange"))))
 '(custom-state-face ((t (:foreground "green3"))))
 '(custom-variable-button-face ((t (:bold t :underline t :foreground "white"))))
 '(dired-face-permissions ((t (:foreground "green3"))))
 '(font-lock-comment-face ((t (:foreground "dark green"))))
 '(font-lock-doc-string-face ((t (:foreground "green3"))))
 '(font-lock-function-name-face ((t (:foreground "blue" :bold t))))
 '(font-lock-keyword-face ((t (:foreground "dark blue"))))
 '(font-lock-preprocessor-face ((t (:foreground "dark red"))))
 '(font-lock-reference-face ((t (:foreground "green3"))))
 '(font-lock-string-face ((t (:foreground "green3"))))
 '(font-lock-type-face ((t (:foreground "#886fff" :bold t))))
 '(font-lock-variable-name-face ((t (:foreground "#9a2fff" :bold t))))
 '(font-lock-warning-face ((t (:foreground "Violetred" :bold t))))
 '(highlight ((t (:foreground "black" :background "white" :bold nil))) t)
 '(isearch ((t (:foreground "red" :background "white"))) t)
 '(list-mode-item-selected ((t (:foreground "green3"))) t)
 '(message-cited-text ((t (:bold t))))
 '(secondary-selection ((t (:foreground "white" :background "red"))) t)
 '(text-cursor ((t (:foreground "black" :background "green3"))) t)
 '(zmacs-region ((t (:background "RoyalBlue"))) t))

;;;;;;;;;;;;;;;;;;;;;;;;;;;
