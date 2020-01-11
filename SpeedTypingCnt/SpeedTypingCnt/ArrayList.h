#pragma once
#include <iostream>

template <typename T, int MAX = 100>
class ArrayList
{
	T m_array[MAX];
	int m_count;

public:
	ArrayList()
	{
		memset(m_array, 0, MAX);
		m_count = 0;
	}
	~ArrayList() {}

	// 데이터 추가
	void Add(T data)
	{
		m_array[m_count] = data;
		m_count++;
	}

	// 데이터 제거
	void Remove(T data)
	{
		RemoveAt(IndexOf(data));
	}

	// 해당 인덱스의 데이터 제거
	T RemoveAt(int index)
	{
		T dataToRemove = m_array[index];
		for (int i = index; i < m_count - 1; i++)
		{
			m_array[i] = m_array[i + 1];
		}
		m_count--;

		return dataToRemove;
	}

	// 해당 인덱스의 데이터 반환
	T GetData(int index)
	{
		if (index < m_count)
		{
			return m_array[index];
		}
		return null;
	}

	// 데이터에 따라 인덱스 반환
	int IndexOf(T data)
	{
		for (int i = 0; i < m_count; I++)
		{
			if (m_array[i] == data) return i;
		}
		return -1;
	}

	// 해당 데이터가 있는지 없는지 여부 반환
	BOOL IsData(T data)
	{
		for (int i = 0; i < m_count; i++)
		{
			if (m_array[i] == data) return TRUE;
		}
		return FALSE;
	}

	// 현재 가지고 있는 데이터 수 반환
	int Count() { return m_count; }
};