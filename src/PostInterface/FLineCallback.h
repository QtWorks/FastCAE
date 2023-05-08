#ifndef _FUNC_LINECALLBACK_H_
#define _FUNC_LINECALLBACK_H_

#include <vtkCommand.h>
#include <QObject>

class vtkLineWidget2;
class vtkLineReprasentation;

class FLineCallback :public QObject, public vtkCommand
{
	Q_OBJECT
public:
	static FLineCallback* New();

	virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData);

	void getLine(double* sPoint, double* ePoint);
	void setLine(double* sPoint, double* ePoint);


signals:
	void updateLineWidgetSig(double* s, double* e);

private:
	FLineCallback();
	~FLineCallback();

private:
	double _startPoint[3]{ 0 };
	double _endPoint[3]{ 1 };
};


#endif