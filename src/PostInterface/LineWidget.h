#ifndef _LINE_WIDGET_H_
#define _LINE_WIDGET_H_

class FLineCallback;
class vtkLineWidget2;
class vtkLineRepresentation;

namespace Post {
	class GraphWidget;
	class RenderDataObject;

	class LineWidget
	{
	public:
		LineWidget(GraphWidget* gw, RenderDataObject* obj);
		~LineWidget();

		FLineCallback* getCallback();
		void setLine(double* sPoint, double* ePoint);
		void getLine(double* sPoint, double* ePoint);

	private:
		FLineCallback* _callback{ nullptr };
		vtkLineRepresentation* _lineRep{ nullptr };
		vtkLineWidget2* _lineWidget{ nullptr };
		GraphWidget* _window{ nullptr };
	};

}

#endif // !_LINE_WIDGET_H_
