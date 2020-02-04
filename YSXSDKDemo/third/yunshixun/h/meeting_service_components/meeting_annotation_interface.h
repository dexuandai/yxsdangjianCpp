#ifndef _YSX_MEETING_Annotation_INTERFACE_H_
#define _YSX_MEETING_Annotation_INTERFACE_H_
#include "..\ysx_sdk_def.h"
#include "..\meeting_service_interface.h"

BEGIN_YSX_SDK_NAMESPACE

///ע�͹�������
enum AnnotationToolType
{
	ANNOTOOL_NONE_DRAWING,///<�л������

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

/// \ע���������
enum AnnotationClearType
{
	ANNOCLEAR_ALL,
	ANNOCLEAR_SELF,
	ANNOCLEAR_OTHER,
};
/// \ע�Ϳ�����
class IAnnotationController
{
public:
	/// \�Ƿ�����ע��
	virtual bool IsAnnoataionDisable() = 0;

	/// \��ʼע��
	virtual SDKError StartAnnotation(SDKViewType viewtype, int left, int top) = 0;

	/// \ֹͣ��ǰע��
	virtual SDKError StopAnnotation(SDKViewType viewtype) = 0;

	/// \����ע�͹���
	virtual SDKError SetTool(SDKViewType viewtype, AnnotationToolType type) = 0;

	/// \���ע��
	virtual SDKError Clear(SDKViewType viewtype, AnnotationClearType type) = 0;


	/// \������ɫ
	virtual SDKError SetColor(SDKViewType viewtype, unsigned long color) = 0;

	/// \�����߿�
	virtual SDKError SetLineWidth(SDKViewType viewtype, long lineWidth) = 0;
	
	/// \����
	virtual SDKError Undo(SDKViewType viewtype) = 0;
	
	/// \����
	virtual SDKError Redo(SDKViewType viewtype) = 0;
};
END_YSX_SDK_NAMESPACE
#endif