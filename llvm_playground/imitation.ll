; ModuleID = 'my cool jit'
source_filename = "my cool jit"

declare i32 @readint()

define i32 @main() {
god_see:
  %calltmp = call i32 @readint()
  ret i32 %calltmp
}
