; ModuleID = 'EduCodeModule'
source_filename = "EduCodeModule"

@str_lit = private unnamed_addr constant [13 x i8] c"N\C3\BAmero par:\00", align 1
@.str = private constant [3 x i8] c"%s\00"
@.str.1 = private constant [3 x i8] c"%d\00"
@.str.2 = private constant [2 x i8] c"\0A\00"
@str_lit.3 = private unnamed_addr constant [15 x i8] c"N\C3\BAmero impar:\00", align 1
@.str.4 = private constant [3 x i8] c"%s\00"
@.str.5 = private constant [3 x i8] c"%d\00"
@.str.6 = private constant [2 x i8] c"\0A\00"

declare i32 @printf(ptr, ...)

declare i32 @scanf(ptr, ...)

define i32 @main() {
entry:
  %contador = alloca i32, align 4
  store i32 0, ptr %contador, align 4
  br label %loopcond

loopcond:                                         ; preds = %ifcont, %entry
  %contador1 = load i32, ptr %contador, align 4
  %cmptmp = icmp slt i32 %contador1, 5
  br i1 %cmptmp, label %loopbody, label %loopend

loopbody:                                         ; preds = %loopcond
  %contador2 = load i32, ptr %contador, align 4
  %modtmp = srem i32 %contador2, 2
  %cmptmp3 = icmp eq i32 %modtmp, 0
  br i1 %cmptmp3, label %then, label %else

then:                                             ; preds = %loopbody
  %contador4 = load i32, ptr %contador, align 4
  %0 = call i32 (ptr, ...) @printf(ptr @.str, ptr @str_lit)
  %1 = call i32 (ptr, ...) @printf(ptr @.str.1, i32 %contador4)
  %2 = call i32 (ptr, ...) @printf(ptr @.str.2)
  br label %ifcont

else:                                             ; preds = %loopbody
  %contador5 = load i32, ptr %contador, align 4
  %3 = call i32 (ptr, ...) @printf(ptr @.str.4, ptr @str_lit.3)
  %4 = call i32 (ptr, ...) @printf(ptr @.str.5, i32 %contador5)
  %5 = call i32 (ptr, ...) @printf(ptr @.str.6)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %contador6 = load i32, ptr %contador, align 4
  %addtmp = add i32 %contador6, 1
  store i32 %addtmp, ptr %contador, align 4
  br label %loopcond

loopend:                                          ; preds = %loopcond
  ret i32 0
}
