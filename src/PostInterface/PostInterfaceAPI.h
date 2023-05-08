#ifndef _POST_INTERFACE_H
#define _POST_INTERFACE_H

#include <QtCore/QtGlobal>

#if defined(POSTINTERFACE_API)
#define POSTINTERFACEAPI Q_DECL_EXPORT
#else
#define POSTINTERFACEAPI Q_DECL_IMPORT
#endif

#endif
