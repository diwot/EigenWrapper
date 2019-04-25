//#pragma once
//
//#include "Mat3x3D.h"
//#include "Vec3D.h"
//#include <cmath>
//
//namespace EigenWrapper
//{
//	public value class Quaternion
//	{
//	public:
//		double W;
//		double X;
//		double Y;
//		double Z;
//
//
//		Quaternion(double w, double x, double y, double z)
//		{
//			X = x;
//			Y = y;
//			Z = z;
//			W = w;
//		}
//
//		Quaternion(Vec3D axis, double angle)
//		{
//			axis.Normalize();
//			double halfAngle = 0.5 * angle;
//			double sin = std::sin(halfAngle);
//			X = axis.X * sin;
//			Y = axis.Y * sin;
//			Z = axis.Z * sin;
//			W = std::cos(halfAngle);
//		}
//
//		property double Norm
//		{
//			double get()
//			{
//				return std::sqrt(X * X + Y * Y + Z * Z + W * W);
//			}
//		}
//
//
//		void Normalize()
//		{
//			double num = 1.0 / std::sqrt(X * X + Y * Y + Z * Z + W * W);
//			X *= num;
//			Y *= num;
//			Z *= num;
//			W *= num;
//		}
//
//		double ScalarPart() { return W; }
//
//		Vec3D VectorPart() { return Vec3D(X, Y, Z); }
//
//		Quaternion Conjugated()
//		{
//			return Quaternion(W, -X, -Y, -Z);
//		}
//
//		static Quaternion operator *(Quaternion l, double r)
//		{
//			l.W = l.W * r;
//			l.X = l.X * r;
//			l.Y = l.Y * r;
//			l.Z = l.Z * r;
//			return l;
//		}
//
//		static Quaternion operator *(double l, Quaternion r)
//		{
//			r.W = l * r.W;
//			r.X = l * r.X;
//			r.Y = l * r.Y;
//			r.Z = l * r.Z;
//			return r;
//		}
//
//		static Quaternion operator *(Quaternion l, Quaternion r)
//		{
//			Quaternion res;
//			res.W = l.W * r.W - l.X * r.X - l.Y * r.Y - l.Z * r.Z;
//			res.X = l.W * r.X + l.X * r.W + l.Y * r.Z - l.Z * r.Y;
//			res.Y = l.W * r.Y + l.Y * r.W + l.Z * r.X - l.X * r.Z;
//			res.Z = l.W * r.Z + l.Z * r.W + l.X * r.Y - l.Y * r.X;
//			return res;
//		}
//
//		static Quaternion FromMatrix(Mat3x3D m)
//		{
//			double trace = m.M11 + m.M22 + m.M33;
//			if (trace > 0.0)
//			{
//				double s = System::Math::Sqrt(trace + 1.0) * 2.0;
//				return Quaternion(0.25 * s, (m.M32 - m.M23) / s, (m.M13 - m.M31) / s, (m.M21 - m.M12) / s);
//			}
//			else if (m.M11 > m.M22 & m.M11 > m.M33)
//			{
//				double s = System::Math::Sqrt(1.0 + m.M11 - m.M22 - m.M33) * 2.0;
//				return Quaternion((m.M32 - m.M23) / s, 0.25 * s, (m.M12 + m.M21) / s, (m.M13 + m.M31) / s);
//			}
//			else if (m.M22 > m.M33)
//			{
//				double s = System::Math::Sqrt(1.0 + m.M22 - m.M11 - m.M33) * 2.0;
//				return Quaternion((m.M13 - m.M31) / s, (m.M12 + m.M21) / s, 0.25 * s, (m.M23 + m.M32) / s);
//			}
//			else 
//			{
//				double s = System::Math::Sqrt(1.0 + m.M33 - m.M11 - m.M22) * 2.0;
//				return Quaternion((m.M21 - m.M12) / s, (m.M13 + m.M31) / s, (m.M23 + m.M32) / s, 0.25 * s);
//			}
//		}
//
//		Mat3x3D ToMatrix()
//		{
//			double xx = X * X;
//			double xy = X * Y;
//			double xz = X * Z;
//			double xw = X * W;
//			double yy = Y * Y;
//			double yz = Y * Z;
//			double yw = Y * W;
//			double zz = Z * Z;
//			double zw = Z * W;
//			Mat3x3D res;
//			res.M11 = 1.0 - 2.0 * (yy + zz);
//			res.M12 = 2.0 * (xy - zw);
//			res.M13 = 2.0 * (xz + yw);
//			res.M21 = 2.0 * (xy + zw);
//			//res.M21 = -res.M12;
//			res.M22 = 1.0 - 2.0 * (xx + zz);
//			res.M23 = 2.0 * (yz - xw);
//			res.M31 = 2.0 * (xz - yw);
//			res.M32 = 2.0 * (yz + xw);
//			//res.M31 = -res.M13;
//			//res.M32 = -res.M23;
//			res.M33 = 1.0 - 2.0 * (xx + yy);
//			return res;
//		}
//	};
//}
//
