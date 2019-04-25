//#pragma once
//
//#include "Vec3D.h"
//
//public value class Mat3x3D
//{
//public:
//	double M11, M12, M13;
//	double M21, M22, M23;
//	double M31, M32, M33;
//
//	Mat3x3D(double m11, double m12, double m13, double m21, double m22, double m23, double m31, double m32, double m33)
//	{
//		M11 = m11;
//		M12 = m12;
//		M13 = m13;
//		M21 = m21;
//		M22 = m22;
//		M23 = m23;
//		M31 = m31;
//		M32 = m32;
//		M33 = m33;
//	}
//
//	static Mat3x3D FromCols(Vec3D^ col0, Vec3D^ col1, Vec3D^ col2)
//	{
//		Mat3x3D r;
//		r.M11 = col0->X; r.M21 = col0->Y; r.M31 = col0->Z;
//		r.M12 = col1->X; r.M22 = col1->Y; r.M32 = col1->Z;
//		r.M13 = col2->X; r.M23 = col2->Y; r.M33 = col2->Z;
//		return r;
//	}
//
//	static Mat3x3D FromRows(Vec3D^ row0, Vec3D^ row1, Vec3D^ row2)
//	{
//		Mat3x3D r;
//		r.M11 = row0->X; r.M12 = row0->Y; r.M13 = row0->Z;
//		r.M21 = row1->X; r.M22 = row1->Y; r.M23 = row1->Z;
//		r.M31 = row2->X; r.M32 = row2->Y; r.M33 = row2->Z;
//		return r;
//	}
//
//	double GetFrobeniusNormSquared()
//	{
//		//https://en.wikipedia.org/wiki/Matrix_norm#Frobenius_norm
//		return M11 * M11 + M12 * M12 + M13 * M13 +
//			M21 * M21 + M22 * M22 + M23 * M23 +
//			M31 * M31 + M32 * M32 + M33 * M33;
//	}
//
//	double Determinant() { return M13 * (M21 * M32 - M22 * M31) + M12 * (M23 * M31 - M21 * M33) + M11 * (M22 * M33 - M23 * M32); }
//
//	void Transpose()
//	{
//		double m = M12;
//		M12 = M21;
//		M21 = m;
//
//		m = M13;
//		M13 = M31;
//		M31 = m;
//
//		m = M23;
//		M23 = M32;
//		M32 = m;
//	}
//
//	static property Mat3x3D Identity
//	{
//		Mat3x3D get()
//		{
//			Mat3x3D res = Mat3x3D();
//			res.M11 = 1; res.M12 = 0; res.M13 = 0;
//			res.M21 = 0; res.M22 = 1; res.M23 = 0;
//			res.M31 = 0; res.M32 = 0; res.M33 = 1;
//			return res;
//		}
//	}
//
//	static Mat3x3D AxisAngle(Vec3D axis, double angleRad)
//	{
//		axis.Normalize();
//
//		double num1 = System::Math::Cos(angleRad * 0.5);
//		double num2 = System::Math::Sin(angleRad * 0.5);
//		double num3 = num2 * axis.X;
//		double num4 = num2 * axis.Y;
//		double num5 = num2 * axis.Z;
//		double num6 = num1 * num1;
//		double num7 = num3 * num3;
//		double num8 = num4 * num4;
//		double num9 = num5 * num5;
//		double num10 = 1.0 / (num7 + num8 + num9 + num6);
//		Mat3x3D rot;
//		rot.M11 = (num7 - num8 - num9 + num6) * num10;
//		rot.M22 = (-num7 + num8 - num9 + num6) * num10;
//		rot.M33 = (-num7 - num8 + num9 + num6) * num10;
//		double num11 = num3 * num4;
//		double num12 = num5 * num1;
//		rot.M21 = 2.0 * (num11 + num12) * num10;
//		rot.M12 = 2.0 * (num11 - num12) * num10;
//		double num13 = num3 * num5;
//		double num14 = num4 * num1;
//		rot.M31 = 2.0 * (num13 - num14) * num10;
//		rot.M13 = 2.0 * (num13 + num14) * num10;
//		double num15 = num4 * num5;
//		double num16 = num3 * num1;
//		rot.M32 = 2.0 * (num15 + num16) * num10;
//		rot.M23 = 2.0 * (num15 - num16) * num10;
//
//		return rot;
//	}
//
//	Mat3x3D Inverted()
//	{
//		return Inverted(1e-16);
//	}
//	Mat3x3D Inverted(double minDetValue)
//	{
//		double det = M13 * (M21 * M32 - M22 * M31) + M12 * (M23 * M31 - M21 * M33) + M11 * (M22 * M33 - M23 * M32);
//		if (System::Math::Abs(det) < minDetValue)
//			throw gcnew System::Exception();
//
//		det = 1.0 / det;
//
//		Mat3x3D result = Mat3x3D();
//		result.M11 = det * (M22 * M33 - M23 * M32);
//		result.M12 = det * (M13 * M32 - M12 * M33);
//		result.M13 = det * (M12 * M23 - M13 * M22);
//
//		result.M21 = det * (M23 * M31 - M21 * M33);
//		result.M22 = det * (M11 * M33 - M13 * M31);
//		result.M23 = det * (M13 * M21 - M11 * M23);
//
//		result.M31 = det * (M21 * M32 - M22 * M31);
//		result.M32 = det * (M12 * M31 - M11 * M32);
//		result.M33 = det * (M11 * M22 - M12 * M21);
//
//		return result;
//	}
//
//	static Mat3x3D operator *(Mat3x3D l, Mat3x3D r)
//	{
//		Mat3x3D result = Mat3x3D();
//		result.M11 = l.M11 * r.M11 + l.M12 * r.M21 + l.M13 * r.M31;
//		result.M12 = l.M11 * r.M12 + l.M12 * r.M22 + l.M13 * r.M32;
//		result.M13 = l.M11 * r.M13 + l.M12 * r.M23 + l.M13 * r.M33;
//
//		result.M21 = l.M21 * r.M11 + l.M22 * r.M21 + l.M23 * r.M31;
//		result.M22 = l.M21 * r.M12 + l.M22 * r.M22 + l.M23 * r.M32;
//		result.M23 = l.M21 * r.M13 + l.M22 * r.M23 + l.M23 * r.M33;
//
//		result.M31 = l.M31 * r.M11 + l.M32 * r.M21 + l.M33 * r.M31;
//		result.M32 = l.M31 * r.M12 + l.M32 * r.M22 + l.M33 * r.M32;
//		result.M33 = l.M31 * r.M13 + l.M32 * r.M23 + l.M33 * r.M33;
//
//		return result;
//	}
//
//	static Vec3D operator *(Mat3x3D l, Vec3D r)
//	{
//		Vec3D result = Vec3D();
//		result.X = l.M11 * r.X + l.M12 * r.Y + l.M13 * r.Z;
//		result.Y = l.M21 * r.X + l.M22 * r.Y + l.M23 * r.Z;
//		result.Z = l.M31 * r.X + l.M32 * r.Y + l.M33 * r.Z;
//
//		return result;
//	}
//
//	static Vec3D operator *(Vec3D l, Mat3x3D r)
//	{
//		Vec3D result = Vec3D();
//		result.X = r.M11 * l.X + r.M21 * l.Y + r.M31 * l.Z;
//		result.Y = r.M12 * l.X + r.M22 * l.Y + r.M32 * l.Z;
//		result.Z = r.M13 * l.X + r.M23 * l.Y + r.M33 * l.Z;
//
//		return result;
//	}
//
//	static Mat3x3D operator *(double l, Mat3x3D r)
//	{
//		r.M11 = l * r.M11;
//		r.M12 = l * r.M12;
//		r.M13 = l * r.M13;
//
//		r.M21 = l * r.M21;
//		r.M22 = l * r.M22;
//		r.M23 = l * r.M23;
//
//		r.M31 = l * r.M31;
//		r.M32 = l * r.M32;
//		r.M33 = l * r.M33;
//
//		return r;
//	}
//
//	static Mat3x3D operator +(Mat3x3D l, Mat3x3D r)
//	{
//		l.M11 = l.M11 + r.M11;
//		l.M12 = l.M12 + r.M12;
//		l.M13 = l.M13 + r.M13;
//
//		l.M21 = l.M21 + r.M21;
//		l.M22 = l.M22 + r.M22;
//		l.M23 = l.M23 + r.M23;
//
//		l.M31 = l.M31 + r.M31;
//		l.M32 = l.M32 + r.M32;
//		l.M33 = l.M33 + r.M33;
//
//		return l;
//	}
//
//	static Mat3x3D operator -(Mat3x3D l, Mat3x3D r)
//	{
//		l.M11 = l.M11 - r.M11;
//		l.M12 = l.M12 - r.M12;
//		l.M13 = l.M13 - r.M13;
//
//		l.M21 = l.M21 - r.M21;
//		l.M22 = l.M22 - r.M22;
//		l.M23 = l.M23 - r.M23;
//
//		l.M31 = l.M31 - r.M31;
//		l.M32 = l.M32 - r.M32;
//		l.M33 = l.M33 - r.M33;
//
//		return l;
//	}
//
//
//	void SetRow0(Vec3D row) { M11 = row.X; M12 = row.Y; M13 = row.Z; }
//	void SetRow1(Vec3D row) { M21 = row.X; M22 = row.Y; M23 = row.Z; }
//	void SetRow2(Vec3D row) { M31 = row.X; M32 = row.Y; M33 = row.Z; }
//
//
//	void SetCol0(Vec3D col)
//	{
//		M11 = col.X;
//		M21 = col.Y;
//		M31 = col.Z;
//	}
//
//	void SetCol1(Vec3D col)
//	{
//		M12 = col.X;
//		M22 = col.Y;
//		M32 = col.Z;
//	}
//
//	void SetCol2(Vec3D col)
//	{
//		M13 = col.X;
//		M23 = col.Y;
//		M33 = col.Z;
//	}
//
//
//	property double default[int, int]
//	{
//		inline double get(int row, int col)
//		{
//			switch (row)
//			{
//			case 0:
//				switch (col)
//				{
//				case 0:
//					return M11;
//				case 1:
//					return M12;
//				case 2:
//					return M13;
//				}
//				break;
//			case 1:
//				switch (col)
//				{
//				case 0:
//					return M21;
//				case 1:
//					return M22;
//				case 2:
//					return M23;
//				}
//				break;
//			case 2:
//				switch (col)
//				{
//				case 0:
//					return M31;
//				case 1:
//					return M32;
//				case 2:
//					return M33;
//				}
//				break;
//			}
//			return 0;
//		}
//		inline void set(int row, int col, double value)
//		{
//			switch (row)
//			{
//			case 0:
//				switch (col)
//				{
//				case 0:
//					M11 = value; break;
//				case 1:
//					M12 = value; break;
//				case 2:
//					M13 = value; break;
//				}
//				break;
//			case 1:
//				switch (col)
//				{
//				case 0:
//					M21 = value; break;
//				case 1:
//					M22 = value; break;
//				case 2:
//					M23 = value; break;
//				}
//				break;
//			case 2:
//				switch (col)
//				{
//				case 0:
//					M31 = value; break;
//				case 1:
//					M32 = value; break;
//				case 2:
//					M33 = value; break;
//				}
//				break;
//			}
//		}
//	}
//
//
//	Vec3D GetCol0() { return Vec3D(M11, M21, M31); }
//	Vec3D GetCol1() { return Vec3D(M12, M22, M32); }
//	Vec3D GetCol2() { return Vec3D(M13, M23, M33); }
//
//	Vec3D GetRow0() { return Vec3D(M11, M12, M13); }
//	Vec3D GetRow1() { return Vec3D(M21, M22, M23); }
//	Vec3D GetRow2() { return Vec3D(M31, M32, M33); }
//
//	//void SetRow0(Vec3D row) { M11 = row.X; M12 = row.Y; M13 = row.Z; }
//	//void SetRow1(Vec3D row) { M21 = row.X; M22 = row.Y; M23 = row.Z; }
//	//void SetRow2(Vec3D row) { M31 = row.X; M32 = row.Y; M33 = row.Z; }
//
//
//
//	Vec3D GetRow(int index)
//	{
//		switch (index)
//		{
//		case 0:
//			return GetRow0();
//		case 1:
//			return GetRow1();
//		case 2:
//			return GetRow2();
//		default:
//			return Vec3D();
//		}
//	}
//
//	void SetRow(int index, Vec3D row)
//	{
//		switch (index)
//		{
//		case 0:
//			SetRow0(row);
//			break;
//		case 1:
//			SetRow1(row);
//			break;
//		case 2:
//			SetRow2(row);
//			break;
//		}
//	}
//};
//
