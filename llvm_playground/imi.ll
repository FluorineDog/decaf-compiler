; ModuleID = 'my cool jit'
source_filename = "my cool jit"

declare i32 @readint()

declare i32 @refint(i32)

define i32 @main() {
god_see:
  %calltmp = call i32 @readint()
  %calltmp1 = call i32 @refint(i32 %calltmp)
  ret i32 %calltmp
}
