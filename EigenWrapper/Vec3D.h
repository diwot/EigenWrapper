//#pragma once
//
//#include <algorithm> 
//
//public value class TetInterpolator
//{
//public:
//	int Length;
//	int A;
//	int B;
//	int C;
//	int D;
//	double WeightA;
//	double WeightB;
//	double WeightC;
//	double WeightD;
//
//	TetInterpolator(int length, int a, int b, int c, int d,
//		double weightA, double weightB, double weightC, double weightD)
//	{
//		Length = length;
//		A = a; B = b; C = c; D = d;
//		WeightA = weightA; WeightB = weightB;
//		WeightC = weightC; WeightD = weightD;
//	}
//};
//
//
//public value class Tri
//{
//public:
//	int A;
//	int B;
//	int C;
//
//	Tri(int a, int b, int c)
//	{
//		A = a;
//		B = b;
//		C = c;
//	}
//
//	virtual int GetHashCode() override
//	{
//		return A ^ B ^ C;
//	}
//
//	virtual bool Equals(System::Object^ obj) override
//	{
//		//if (obj == nullptr || GetType() != obj->GetType())
//		//	return false;
//
//		Tri v = safe_cast<Tri>(obj);
//		return A==v.A && B==v.B && C==v.C;
//	}
//
//
//
//	void Sort()
//	{
//		int tmp;
//		if (A > B)
//		{
//			tmp = A;
//			A = B;
//			B = tmp;
//		}
//		if (B > C)
//		{
//			tmp = B;
//			B = C;
//			C = tmp;
//		}
//		if (A > B)
//		{
//			tmp = A;
//			A = B;
//			B = tmp;
//		}
//	}
//
//
//	virtual System::String^ ToString() override
//	{
//		return A.ToString() + "   " + B.ToString() + "   " + C.ToString();
//	}
//};
//
//
//
//
//
//public value class Vec3D
//{
//public:
//	static initonly Vec3D Zero = Vec3D(0, 0, 0);
//	static initonly Vec3D UnitX = Vec3D(1, 0, 0);
//	static initonly Vec3D UnitY = Vec3D(0, 1, 0);
//	static initonly Vec3D UnitZ = Vec3D(0, 0, 1);
//
//
//	double X;
//	double Y;
//	double Z;
//
//	Vec3D(double x, double y, double z)
//	{
//		X = x;
//		Y = y;
//		Z = z;
//	}
//
//	
//
//	property double Length
//	{
//		double get() { return System::Math::Sqrt(X * X + Y * Y + Z * Z); }
//	}
//
//	property double LengthSquared
//	{
//		double get() { return X * X + Y * Y + Z * Z; }
//	}
//
//	static Vec3D GetPerpendicularVector(Vec3D axis)
//	{
//		double x = axis.X >= 0.0 ? axis.X : -axis.X;
//		double y = axis.Y >= 0.0 ? axis.Y : -axis.Y;
//		double z = axis.Z >= 0.0 ? axis.Z : -axis.Z;
//		if (x >= y && x >= z)
//			return Cross(axis, Vec3D(0.0, 1.0, 0.0));
//		if (y >= x && y >= z)
//			return Cross(axis, Vec3D(0.0, 0.0, 1.0));
//		if (z >= x && z >= y)
//			return Cross(axis, Vec3D(1.0, 0.0, 0.0));		
//	}
//
//	static double SquaredDistance(Vec3D a, Vec3D b)
//	{
//		double dx = b.X - a.X;
//		double dy = b.Y - a.Y;
//		double dz = b.Z - a.Z;
//		return dx*dx + dy*dy + dz*dz;
//	}
//
//	static double Distance(Vec3D a, Vec3D b)
//	{
//		double dx = b.X - a.X;
//		double dy = b.Y - a.Y;
//		double dz = b.Z - a.Z;
//		return System::Math::Sqrt(dx*dx + dy*dy + dz*dz);
//	}
//
//	static double Magnitude(Vec3D vec)
//	{
//		return System::Math::Sqrt(vec.X*vec.X + vec.Y*vec.Y + vec.Z*vec.Z);
//	}
//
//	void Set(double x, double y, double z)
//	{
//		X = x;
//		Y = y;
//		Z = z;
//	}
//
//	void Normalize()
//	{
//		double d = X * X + Y * Y + Z * Z;
//		if (d > 1e-16)
//		{
//			d = 1.0 / System::Math::Sqrt(d);
//			X *= d;
//			Y *= d;
//			Z *= d;
//		}
//	}
//	Vec3D Normalized()
//	{
//		Vec3D copy = Vec3D(X, Y, Z);
//		double d = X * X + Y * Y + Z * Z;
//		if (d > 1e-16)
//		{
//			d = 1.0 / System::Math::Sqrt(d);
//			copy.X *= d;
//			copy.Y *= d;
//			copy.Z *= d;
//		}
//		return copy;
//	}
//
//	static bool operator ==(Vec3D l, Vec3D r)
//	{
//		return l.X == r.X && l.Y == r.Y && l.Z == r.Z;
//	}
//
//	static bool operator !=(Vec3D l, Vec3D r)
//	{
//		return l.X != r.X || l.Y != r.Y || l.Z != r.Z;
//	}
//
//	static Vec3D operator -(Vec3D l, Vec3D r)
//	{
//		l.X = l.X - r.X;
//		l.Y = l.Y - r.Y;
//		l.Z = l.Z - r.Z;
//		return l;
//	}
//	static Vec3D operator +(Vec3D l, Vec3D r)
//	{
//		l.X = l.X + r.X;
//		l.Y = l.Y + r.Y;
//		l.Z = l.Z + r.Z;
//		return l;
//	}
//
//	static Vec3D operator *(double l, Vec3D r)
//	{
//		r.X = l * r.X;
//		r.Y = l * r.Y;
//		r.Z = l * r.Z;
//		return r;
//	}
//
//	static Vec3D operator *(Vec3D l, double r)
//	{
//		l.X = l.X * r;
//		l.Y = l.Y * r;
//		l.Z = l.Z * r;
//		return l;
//	}
//
//	static double Dot(Vec3D a, Vec3D b)
//	{
//		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
//	}
//
//	static Vec3D Cross(Vec3D left, Vec3D right)
//	{
//		return Vec3D(left.Y * right.Z - left.Z * right.Y,
//			left.Z * right.X - left.X * right.Z,
//			left.X * right.Y - left.Y * right.X);
//	}
//
//	virtual bool Equals(System::Object^ obj) override
//	{
//		//if (obj == nullptr || GetType() != obj->GetType())
//		//	return false;
//
//		Vec3D v = safe_cast<Vec3D>(obj);
//		return X==v.X && Y==v.Y && Z==v.Z;;
//	}
//
//	virtual int GetHashCode() override
//	{
//		return X.GetHashCode() ^ Y.GetHashCode() ^ Z.GetHashCode();
//	}
//
//	virtual System::String^ ToString() override
//	{
//		return X.ToString() + ", " + Y.ToString() + ", " + Z.ToString();
//	}
//
//	property double default[int]
//	{
//		inline double get(int index)
//		{
//			switch (index)
//			{
//			case 0:
//				return X;
//			case 1:
//				return Y;
//			case 2:
//				return Z;
//			}
//			return 0;
//		}
//		inline void set(int index, double value)
//		{
//			switch (index)
//			{
//			case 0:
//				X = value;
//				break;
//			case 1:
//				Y = value;
//				break;
//			case 2:
//				Z = value;
//				break;
//			}
//		}
//	}
//};
//
//
//
//public value class Tet
//{
//public:
//	int A;
//	int B;
//	int C;
//	int D;
//
//	Tet(int a, int b, int c, int d)
//	{
//		A = a;
//		B = b;
//		C = c;
//		D = d;
//	}
//
//	static double Volume(Tet tet, System::Collections::Generic::IList<Vec3D>^ points)
//	{
//		return (1.0 / 6.0) * System::Math::Abs(Vec3D::Dot(points[tet.A] - points[tet.D], Vec3D::Cross(points[tet.B] - points[tet.D], points[tet.C] - points[tet.D])));
//	}
//
//	//TODO: Not sure if the sign is correct
//	//TODO: Optimize performance by hand-inlining
//	static double SignedVolume(Tet tet, System::Collections::Generic::IList<Vec3D>^ points)
//	{
//		return (-1.0 / 6.0) * Vec3D::Dot(points[tet.A] - points[tet.D], Vec3D::Cross(points[tet.B] - points[tet.D], points[tet.C] - points[tet.D]));
//	}
//
//	virtual System::String^ ToString() override
//	{
//		return A.ToString() + "   " + B.ToString() + "   " + C.ToString() + "   " + D.ToString();
//	}
//
//	void Sort()
//	{
//		int buffer[] { A, B, C, D };
//		std::sort(buffer, buffer + 4);
//		A = buffer[0];
//		B = buffer[1];
//		C = buffer[2];
//		D = buffer[3];
//	}
//};
//
