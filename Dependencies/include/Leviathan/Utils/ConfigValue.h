#pragma once

class ConfigValue
{
public:
	ConfigValue(void* _value) : m_value(_value) {}
	~ConfigValue() { delete m_value; }
	
	template<typename VAL>
	VAL Get();

private:
	void* m_value;

};

template<typename VAL>
VAL ConfigValue::Get()
{
	return *((VAL*)m_value);
}
