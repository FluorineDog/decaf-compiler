; ModuleID = 'my cool jit'
source_filename = "my cool jit"

declare i32 @readint()

declare i32 @refint(i32)

define i32 @main() {
god_see:
  %tmp = alloca i32
  store i32 100, i32* %tmp
  %ld = load i32, i32* %tmp
  %calltmp = call i32 @readint()
  %addtmp = add i32 %ld, %calltmp
  %calltmp1 = call i32 @refint(i32 %addtmp)
  ret i32 %calltmp
}
