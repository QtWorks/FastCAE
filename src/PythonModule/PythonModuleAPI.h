﻿#ifndef PYTHONMODULEAPI_H
#define PYTHONMODULEAPI_H

#include <QtCore/QtGlobal>

#if defined(PYTHONMODULE_API)
#define PYTHONMODULEAPI Q_DECL_EXPORT
#else
#define PYTHONMODULEAPI Q_DECL_IMPORT
#endif

#endif // PYTHONMODULEAPI_H
