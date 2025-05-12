#pragma once

#include <matrix/matrix/math.hpp>
#include <lib/mixer/MultirorMixer/MultirotorMixer.hpp>








// class TrackingDifferentiator
// {
// public:
// 	TrackingDifferentiator(){reset();};
// 	~TrackingDifferentiator(){};

// 	void set_td_coef(const float a0,const float a1)
// 	{
// 		_a0 = a0;
// 		_a1 = a1;
// 	}
//         void set_td_ratio_frequency(const float xi,const float wn)
// 	{
// 		_a0 = wn*wn;
// 		_a1 = 2.0f* xi*wn;
// 	}
// 	void update(const float input,const float dt)
// 	{
// 		v = input;
// 		v1 =

// 	}
// }



class TrackingDifferentiator
{
public:
	TrackingDifferentiator() { reset(); }
	~TrackingDifferentiator() {}

	void set_td_coef(const float a0, const float a1)
	{
		_a0 = a0;
		_a1 = a1;
	}

	void set_td_ratio_frequency(const float xi, const float wn)
	{
		_a0 = wn * wn;
		_a1 = 2.0f * xi * wn;
	}

	void update(const float input, const float dt)
	{
		v = input;

		// 二阶线性系统差分更新
		float e = v1 - v;
		v2 += (-_a0 * e - _a1 * v2) * dt;
		v1 += v2 * dt;
	}

	void reset()
	{
		v = 0.0f;
		v1 = 0.0f;
		v2 = 0.0f;
		_a0 = 1.0f;
		_a1 = 1.0f;
	}

	float get_v1() const { return v1; } // 跟踪值
	float get_v2() const { return v2; } // 跟踪导数

private:
	float v = 0.0f;   // 输入
	float v1 = 0.0f;  // 跟踪值
	float v2 = 0.0f;  // 跟踪导数
	float _a0 = 1.0f;
	float _a1 = 1.0f;
};
