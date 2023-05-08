#ifndef COMMONAPI_H
#define COMMONAPI_H

#include <QtCore/QtGlobal>

#ifdef COMMON_API
#define COMMONAPI Q_DECL_EXPORT
#else
#define COMMONAPI Q_DECL_IMPORT
#endif

#endif // PYTHONMODULEAPI_H
