; ModuleID = 'ocbuild.mm'
source_filename = "ocbuild.mm"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx13.0.0"

%0 = type opaque
%struct._class_t = type { %struct._class_t*, %struct._class_t*, %struct._objc_cache*, i8* (i8*, i8*)**, %struct._class_ro_t* }
%struct._objc_cache = type opaque
%struct._class_ro_t = type { i32, i32, i32, i8*, i8*, %struct.__method_list_t*, %struct._objc_protocol_list*, %struct._ivar_list_t*, i8*, %struct._prop_list_t* }
%struct.__method_list_t = type { i32, i32, [0 x %struct._objc_method] }
%struct._objc_method = type { i8*, i8*, i8* }
%struct._objc_protocol_list = type { i64, [0 x %struct._protocol_t*] }
%struct._protocol_t = type { i8*, i8*, %struct._objc_protocol_list*, %struct.__method_list_t*, %struct.__method_list_t*, %struct.__method_list_t*, %struct.__method_list_t*, %struct._prop_list_t*, i32, i32, i8**, i8*, %struct._prop_list_t* }
%struct._ivar_list_t = type { i32, i32, [0 x %struct._ivar_t] }
%struct._ivar_t = type { i64*, i8*, i8*, i32, i32 }
%struct._prop_list_t = type { i32, i32, [0 x %struct._prop_t] }
%struct._prop_t = type { i8*, i8* }
%struct.__NSConstantString_tag = type { i32*, i32, i8*, i64 }

@"OBJC_CLASS_$_NSString" = external global %struct._class_t
@"OBJC_CLASSLIST_REFERENCES_$_" = internal global %struct._class_t* @"OBJC_CLASS_$_NSString", section "__DATA,__objc_classrefs,regular,no_dead_strip", align 8
@.str = private unnamed_addr constant [9 x i8] c"starming\00", align 1
@OBJC_METH_VAR_NAME_ = private unnamed_addr constant [20 x i8] c"initWithUTF8String:\00", section "__TEXT,__objc_methname,cstring_literals", align 1
@OBJC_SELECTOR_REFERENCES_ = internal externally_initialized global i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_, i64 0, i64 0), section "__DATA,__objc_selrefs,literal_pointers,no_dead_strip", align 8
@__CFConstantStringClassReference = external global [0 x i32]
@.str.1 = private unnamed_addr constant [11 x i8] c"%@ rank %d\00", section "__TEXT,__cstring,cstring_literals", align 1
@_unnamed_cfstring_ = private global %struct.__NSConstantString_tag { i32* getelementptr inbounds ([0 x i32], [0 x i32]* @__CFConstantStringClassReference, i32 0, i32 0), i32 1992, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.1, i32 0, i32 0), i64 10 }, section "__DATA,__cfstring", align 8 #0
@llvm.compiler.used = appending global [3 x i8*] [i8* bitcast (%struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_" to i8*), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @OBJC_METH_VAR_NAME_, i32 0, i32 0), i8* bitcast (i8** @OBJC_SELECTOR_REFERENCES_ to i8*)], section "llvm.metadata"

; Function Attrs: norecurse ssp uwtable
define i32 @main() local_unnamed_addr #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = tail call i8* @llvm.objc.autoreleasePoolPush() #2
  %2 = load i8*, i8** bitcast (%struct._class_t** @"OBJC_CLASSLIST_REFERENCES_$_" to i8**), align 8
  %3 = tail call i8* @objc_alloc(i8* %2)
  %4 = load i8*, i8** @OBJC_SELECTOR_REFERENCES_, align 8, !invariant.load !12
  %5 = tail call i8* bitcast (i8* (i8*, i8*, ...)* @objc_msgSend to i8* (i8*, i8*, i8*)*)(i8* noundef %3, i8* noundef %4, i8* noundef getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i64 0, i64 0))
  invoke void (%0*, ...) @NSLog(%0* noundef bitcast (%struct.__NSConstantString_tag* @_unnamed_cfstring_ to %0*), i8* noundef %5, i32 noundef 14)
          to label %6 unwind label %7

6:                                                ; preds = %0
  tail call void @llvm.objc.release(i8* %5) #2, !clang.imprecise_release !12
  tail call void @llvm.objc.autoreleasePoolPop(i8* %1) #2
  ret i32 0

7:                                                ; preds = %0
  %8 = landingpad { i8*, i32 }
          cleanup
  tail call void @llvm.objc.release(i8* %5) #2, !clang.imprecise_release !12
  resume { i8*, i32 } %8
}

; Function Attrs: nounwind
declare i8* @llvm.objc.autoreleasePoolPush() #2

declare i8* @objc_alloc(i8*) local_unnamed_addr

; Function Attrs: nonlazybind
declare i8* @objc_msgSend(i8*, i8*, ...) local_unnamed_addr #3

declare void @NSLog(%0* noundef, ...) local_unnamed_addr #4

; Function Attrs: nounwind
declare void @llvm.objc.release(i8*) #2

; Function Attrs: nounwind
declare void @llvm.objc.autoreleasePoolPop(i8*) #2

declare i32 @__gxx_personality_v0(...)

attributes #0 = { "objc_arc_inert" }
attributes #1 = { norecurse ssp uwtable "darwin-stkchk-strong-link" "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind }
attributes #3 = { nonlazybind }
attributes #4 = { "darwin-stkchk-strong-link" "frame-pointer"="all" "no-trapping-math"="true" "probe-stack"="___chkstk_darwin" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4, !5, !6, !7, !8, !9, !10}
!llvm.ident = !{!11}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 13, i32 3]}
!1 = !{i32 1, !"Objective-C Version", i32 2}
!2 = !{i32 1, !"Objective-C Image Info Version", i32 0}
!3 = !{i32 1, !"Objective-C Image Info Section", !"__DATA,__objc_imageinfo,regular,no_dead_strip"}
!4 = !{i32 1, !"Objective-C Garbage Collection", i8 0}
!5 = !{i32 1, !"Objective-C Class Properties", i32 64}
!6 = !{i32 1, !"Objective-C Enforce ClassRO Pointer Signing", i8 0}
!7 = !{i32 1, !"wchar_size", i32 4}
!8 = !{i32 7, !"PIC Level", i32 2}
!9 = !{i32 7, !"uwtable", i32 2}
!10 = !{i32 7, !"frame-pointer", i32 2}
!11 = !{!"Apple clang version 14.0.3 (clang-1403.0.22.14.1)"}
!12 = !{}
