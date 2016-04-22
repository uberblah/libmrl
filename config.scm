
(define srcdir "mrl")
(define objdir "obj")
(define libdir "lib")

(define cc "gcc")
(define ar "ar")
(define cflags "-I.")
(define ldflags "")

(define (srcfile? path)
  (and (string-match ".c$" path) #t))
(define (header? path)
  (and (string-match ".h$" path) #t))
(define (objfile? path)
  (and (string-match ".o$" path) #t))

(define (compile srcfile outname)
  (define cmd (string-append cc " " cflags " -c " srcfile " -o " outname))
  (runcmd cmd))
  ;;(display cmd) (newline)
  ;;(primitive-eval cmd))

(define (link srcfiles outname)
  (define cmd (string-append ar " rcs " outname " " (string-join srcfiles " ")))
  (runcmd cmd))
  ;;(display cmd) (newline)
  ;;(primitive-eval cmd))
