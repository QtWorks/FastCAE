﻿#ifndef POSTCURVEDATAMANAGERAPI_H
#define POSTCURVEDATAMANAGERAPI_H

#include <QtCore/QtGlobal>

#if defined(POSTCURVEDATAMANAGER_API)
#define POSTCURVEDATAMANAGERAPI Q_DECL_EXPORT
#else
#define POSTCURVEDATAMANAGERAPI Q_DECL_IMPORT
#endif

#endif // POSTCURVEDATAMANAGERAPI_H
