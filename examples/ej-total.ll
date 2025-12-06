; ModuleID = 'EduCodeModule'
source_filename = "EduCodeModule"

@str_lit = private unnamed_addr constant [5 x i8] c"Juan\00", align 1
@str_lit.1 = private unnamed_addr constant [5 x i8] c"Hola\00", align 1
@str_lit.2 = private unnamed_addr constant [11 x i8] c"tu edad es\00", align 1
@.str = private constant [3 x i8] c"%s\00"
@.str.3 = private constant [3 x i8] c"%s\00"
@.str.4 = private constant [3 x i8] c"%s\00"
@.str.5 = private constant [3 x i8] c"%d\00"
@.str.6 = private constant [2 x i8] c"\0A\00"
@str_lit.7 = private unnamed_addr constant [19 x i8] c"Eres mayor de edad\00", align 1
@.str.8 = private constant [3 x i8] c"%s\00"
@.str.9 = private constant [2 x i8] c"\0A\00"
@str_lit.10 = private unnamed_addr constant [19 x i8] c"Eres menor de edad\00", align 1
@.str.11 = private constant [3 x i8] c"%s\00"
@.str.12 = private constant [2 x i8] c"\0A\00"
@.str.13 = private constant [3 x i8] c"%d\00"
@.str.14 = private constant [2 x i8] c"\0A\00"
@.str.15 = private constant [3 x i8] c"%s\00"
@.str.16 = private constant [3 x i8] c"%d\00"
@.str.17 = private constant [3 x i8] c"%d\00"
@.str.18 = private constant [2 x i8] c"\0A\00"

declare i32 @printf(ptr, ...)

declare i32 @scanf(ptr, ...)

define i32 @main() {
entry:
  %edad = alloca i32, align 4
  store i32 25, ptr %edad, align 4
  %0 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str, ptr nonnull @str_lit.1)
  %1 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.3, ptr nonnull @str_lit)
  %2 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.4, ptr nonnull @str_lit.2)
  %3 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.5, i32 25)
  %putchar = call i32 @putchar(i32 10)
  br i1 true, label %then, label %else

then:                                             ; preds = %entry
  %4 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.8, ptr nonnull @str_lit.7)
  %putchar10 = call i32 @putchar(i32 10)
  br label %ifcont

else:                                             ; preds = %entry
  %5 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.11, ptr nonnull @str_lit.10)
  %putchar9 = call i32 @putchar(i32 10)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  br label %foreachcond

foreachcond:                                      ; preds = %foreachcond, %ifcont
  %6 = call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.13, i32 0)
  %putchar11 = call i32 @putchar(i32 10)
  br label %foreachcond
}

; Function Attrs: nofree nounwind
declare noundef i32 @putchar(i32 noundef) #0

attributes #0 = { nofree nounwind }
