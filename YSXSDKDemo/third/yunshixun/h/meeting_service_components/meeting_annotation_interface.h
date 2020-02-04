#ifndef _YSX_MEETING_Annotation_INTERFACE_H_
#define _YSX_MEETING_Annotation_INTERFACE_H_
#include "..\ysx_sdk_def.h"
#include "..\meeting_service_interface.h"

BEGIN_YSX_SDK_NAMESPACE

///注释工具类型
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<切换到鼠标

	ANNOTOOL_PEN,
	ANNOTOOL_HIGHLIGHTER,
	ANNOTOOL_AUTO_LINE,
	ANNOTOOL_AUTO_RECTANGLE,
	ANNOTOOL_AUTO_ELLIPSE,
	ANNOTOOL_AUTO_ARROW,
	ANNOTOOL_AUTO_RECTANGLE_FILL,
	ANNOTOOL_AUTO_ELLIPSE_FILL,

	ANNOTOOL_SPOTLIGHT,
	ANNOTOOL_ARROW,

	ANNOTOOL_ERASER,	///<earser
};

/// \注释清空类型
enum AnnotationClearType
{
	ANNOCLEAR_ALL,
	ANNOCLEAR_SELF,
	ANNOCLEAR_OTHER,
};
/// \注释控制器
class IAnnotationController
{
public:
	/// \是否启用注释
	virtual bool IsAnnoataionDisable() = 0;

	/// \开始注释
	virtual SDKError StartAnnotation(SDKViewType viewtype, int left, int top) = 0;

	/// \停止当前注释
	virtual SDKError StopAnnotation(SDKViewType viewtype) = 0;

	/// \设置注释工具
	virtual SDKError SetTool(SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \清空注释
	virtual SDKError Clear(SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \设置颜色
	virtual SDKError SetColor(SDKViewType viewtype, unsigned long color) = 0;

	/// \设置线宽
	virtual SDKError SetLineWidth(SDKViewType viewtype, long lineWidth) = 0;
	
	/// \撤销
	virtual SDKError Undo(SDKViewType viewtype) = 0;
	
	/// \重做
	virtual SDKError Redo(SDKViewType viewtype) = 0;
};
END_YSX_SDK_NAMESPACE
#endif