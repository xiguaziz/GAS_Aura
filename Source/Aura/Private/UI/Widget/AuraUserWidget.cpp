// Aura学习中。


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController=InWidgetController;
	WidgetControllerSet();
}
