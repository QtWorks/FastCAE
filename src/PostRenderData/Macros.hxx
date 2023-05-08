#ifndef _POST3D_MACROS_H_
#define _POST3D_MACROS_H_

#include <QtGlobal>

#ifdef Q_OS_WIN

/**
 * @brief 前置声明
 */
#define ForwardDeclar(aClass) class aClass;

 /**
  * @brief 带命名空间的前置声明
  */
#define ForwardDeclarNS(aNamespace,aClass) namespace aNamespace {class aClass;}

  /**
   * @brief 声明属性(...为初始化值)并添加set get函数
   */
#define AddProperty(AType, AVariable, ...)   private: AType _##AVariable{##__VA_ARGS__}; \
                                             public: \
                                                  virtual void set##AVariable(AType V)  {_##AVariable = V;} \
                                                  virtual AType get##AVariable() const {return _##AVariable;}
   /**
     * @brief 声明属性(...为初始化值)并添加set函数
     */
#define AddPropertyWriteOnly(AType, AVariable, ...)   private: AType _##AVariable{##__VA_ARGS__}; \
                                             public: \
                                                virtual  void set##AVariable(AType V) {_##AVariable = V;}

   /**
   * @brief 声明属性(...为初始化值)并添加get函数
   */
#define AddPropertyReadOnly(AType, AVariable, ...)   private: AType _##AVariable{##__VA_ARGS__}; \
                                             public: \
                                                virtual  AType get##AVariable() const  {return _##AVariable;}


   /**
   * @brief 声明属性(...为初始化值)并添加set get函数, get函数未实现
   */
#define AddPropertyGetOverride(AType, AVariable, ...)   private: AType _##AVariable{##__VA_ARGS__}; \
                                             public: \
                                                 virtual void set##AVariable(AType V) {_##AVariable = V;}\
                                                 virtual AType get##AVariable();

   /**
   * @brief 声明属性(...为初始化值)并添加set get函数, set函数未实现
   */
#define AddPropertySetOverride(AType, AVariable, ...)   private: AType _##AVariable{##__VA_ARGS__}; \
                                             public: \
                                                 virtual void set##AVariable(AType V);\
                                                 virtual AType get##AVariable() {return _##AVariable;}

   /**
   * @brief 声明属性(...为初始化值)并添加set get函数, get set函数均未实现
   */
#define AddComplexProperty(AType, AVariable, ...)   private: AType _##AVariable{##__VA_ARGS__}; \
                                             public: \
                                                 virtual void set##AVariable(AType V) ; \
                                                 virtual AType get##AVariable();
   /**
   * @brief 声明指针链表属性(...为访问权限，默认私有)
   */
#define AddPtrListProperty(AType, AVariable, ...)  private: ##__VA_ARGS__ QList<AType*> _##AVariable{}; \
                                              public: \
                                                  int get##AVariable##Count(){return _##AVariable.size();} \
                                                  void append##AVariable(AType* v){_##AVariable.append(v);} \
                                                  AType* get##AVariable##At(int index)  \
                                                  {if(index<0 || index >= _##AVariable.size()) return nullptr;\
                                                   return _##AVariable.at(index); }

   /**
   * @brief 声明对象链表属性(...为访问权限，默认私有)
   */
#define AddListProperty(AType, AVariable, ...)  private: ##__VA_ARGS__ QList<AType> _##AVariable{}; \
                                              public: \
                                                  virtual int get##AVariable##Count(){return _##AVariable.size();} \
                                                  virtual void append##AVariable(AType v){if(!_##AVariable.contains(v)) _##AVariable.append(v);} \
                                                  virtual AType get##AVariable##At(int index)  \
                                                  {if(index<0 || index >= _##AVariable.size()) return AType();\
                                                   return _##AVariable.at(index); }\
                                                   virtual void clear##AVariable(){_##AVariable.clear();}
/**
* @brief 删除对象
*/
#define DeleteItem(item) if(item!=nullptr){delete item; item = nullptr;}


/**
* @brief 自动分配ID宏定义
*/
#define AutoDistributeID  public:  int getID() {return _id;} \
                                   static int getMaxID() {return MaxID;} \
                          protected: int _id{ 0 }; \
                                     void setID(int id) {_id = id;} \
                          private:  static int MaxID;

/**
 * @brief 单例宏定义
 */
#define Singleton(thisClass) private: static thisClass* _instance; \
                                thisClass(){this->initialize();} \
                                ~thisClass() = default; \
                                public: \
                                static thisClass* getInstance(){\
                                   if(_instance == nullptr) \
                                       _instance = new thisClass;\
                                   return _instance;}

 /**
 * @brief 声明VTK智能指针, Type Vtk类型 Variable 变量名
 */
#define DeclarVTKSmartPtr(Type,Variable)  vtkSmartPointer<Type> Variable{nullptr};

 /**
 * @brief 创建VTK智能指针, Variable必须是已经声明的变量  Type Vtk类型 Variable 变量名
 */
#define CreateVTKSmartPtr(Type,Variable)  Variable = vtkSmartPointer<Type>::New();

 /**
 * @brief 声明并创建VTK智能指针, Type Vtk类型 Variable 变量名
 */
#define DecCreVTKSmartPtr(Type,Variable)  vtkSmartPointer<Type> Variable = vtkSmartPointer<Type>::New();


 /**
 * @brief 声明并创建VTK指针, Type Vtk类型 Variable 变量名
 */
#define DecCreVTKPtr(Type,Variable)  Type* Variable = Type::New();

/**
 *QString 转char*
 */
#define QString2Char(QSTRING, CCHAR) QByteArray ba = QSTRING.toLatin1(); \
                                     char* CCHAR = ba.data();

 /**
  *char* 转 QString
  */
#define Char2QString(CCHAR, QSTRING) QString QSTRING = QString::fromLocal8Bit(CCHAR);

#else

/**
 * @brief 前置声明
 */
#define ForwardDeclar(aClass) class aClass;

/**
  * @brief 带命名空间的前置声明
  */
#define ForwardDeclarNS(aNamespace,aClass) namespace aNamespace {class aClass;}

/**
   * @brief 声明属性(...为初始化值)并添加set get函数
   */
#define AddProperty(AType, AVariable, args...)   private: AType _##AVariable{args}; \
    public: \
    virtual void set##AVariable(AType V)  {_##AVariable = V;} \
    virtual AType get##AVariable() const {return _##AVariable;}
/**
         * @brief 声明属性(...为初始化值)并添加set函数
         */
#define AddPropertyWriteOnly(AType, AVariable, args...)   private: AType _##AVariable{args}; \
    public: \
    virtual  void set##AVariable(AType V) {_##AVariable = V;}

/**
   * @brief 声明属性(...为初始化值)并添加get函数
   */
#define AddPropertyReadOnly(AType, AVariable, args...)   private: AType _##AVariable{args}; \
    public: \
    virtual  AType get##AVariable() const  {return _##AVariable;}


/**
   * @brief 声明属性(...为初始化值)并添加set get函数, get函数未实现
   */
#define AddPropertyGetOverride(AType, AVariable, args...)   private: AType _##AVariable{args}; \
    public: \
    virtual void set##AVariable(AType V) {_##AVariable = V;}\
    virtual AType get##AVariable();

/**
   * @brief 声明属性(...为初始化值)并添加set get函数, set函数未实现
   */
#define AddPropertySetOverride(AType, AVariable, args...)   private: AType _##AVariable{args}; \
    public: \
    virtual void set##AVariable(AType V);\
    virtual AType get##AVariable() {return _##AVariable;}

/**
   * @brief 声明属性(...为初始化值)并添加set get函数, get set函数均未实现
   */
#define AddComplexProperty(AType, AVariable, args...)   private: AType _##AVariable{args}; \
    public: \
    virtual void set##AVariable(AType V) ; \
    virtual AType get##AVariable();
/**
   * @brief 声明指针链表属性(...为访问权限，默认私有)
   */
#define AddPtrListProperty(AType, AVariable, args...)  private: args QList<AType*> _##AVariable{}; \
    public: \
    int get##AVariable##Count(){return _##AVariable.size();} \
    void append##AVariable(AType* v){_##AVariable.append(v);} \
    AType* get##AVariable##At(int index)  \
{if(index<0 || index >= _##AVariable.size()) return nullptr;\
    return _##AVariable.at(index); }

/**
   * @brief 声明对象链表属性(...为访问权限，默认私有)
   */
#define AddListProperty(AType, AVariable, args...)  private: args QList<AType> _##AVariable{}; \
    public: \
    virtual int get##AVariable##Count(){return _##AVariable.size();} \
    virtual void append##AVariable(AType v){if(!_##AVariable.contains(v)) _##AVariable.append(v);} \
    virtual AType get##AVariable##At(int index)  \
{if(index<0 || index >= _##AVariable.size()) return AType();\
    return _##AVariable.at(index); }\
    virtual void clear##AVariable(){_##AVariable.clear();}
/**
* @brief 删除对象
*/
#define DeleteItem(item) if(item!=nullptr){delete item; item = nullptr;}


/**
* @brief 自动分配ID宏定义
*/
#define AutoDistributeID  public:  int getID() {return _id;} \
    static int getMaxID() {return MaxID;} \
    protected: int _id{ 0 }; \
    void setID(int id) {_id = id;} \
    private:  static int MaxID;

/**
 * @brief 单例宏定义
 */
#define Singleton(thisClass) private: static thisClass* _instance; \
    thisClass(){this->initialize();} \
    ~thisClass() = default; \
    public: \
    static thisClass* getInstance(){\
    if(_instance == nullptr) \
    _instance = new thisClass;\
    return _instance;}

/**
 * @brief 声明VTK智能指针, Type Vtk类型 Variable 变量名
 */
#define DeclarVTKSmartPtr(Type,Variable)  vtkSmartPointer<Type> Variable{nullptr};

/**
 * @brief 创建VTK智能指针, Variable必须是已经声明的变量  Type Vtk类型 Variable 变量名
 */
#define CreateVTKSmartPtr(Type,Variable)  Variable = vtkSmartPointer<Type>::New();

/**
 * @brief 声明并创建VTK智能指针, Type Vtk类型 Variable 变量名
 */
#define DecCreVTKSmartPtr(Type,Variable)  vtkSmartPointer<Type> Variable = vtkSmartPointer<Type>::New();


/**
 * @brief 声明并创建VTK指针, Type Vtk类型 Variable 变量名
 */
#define DecCreVTKPtr(Type,Variable)  Type* Variable = Type::New();

/**
 *QString 转char*
 */
#define QString2Char(QSTRING, CCHAR) QByteArray ba = QSTRING.toLatin1(); \
    char* CCHAR = ba.data();

/**
  *char* 转 QString
  */
#define Char2QString(CCHAR, QSTRING) QString QSTRING = QString::fromLocal8Bit(CCHAR);

#endif
#endif
