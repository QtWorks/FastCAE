template <typename T>
class Singleton
{
public:
	static T *&instance()
	{
		return m_Instance;
	}

	Singleton(T &&) = delete;
	Singleton(const T &) = delete;
	void operator=(const T &) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

private:
	static T *m_Instance;
};

template <typename T>
T *Singleton<T>::m_Instance = new T;