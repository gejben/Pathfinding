#ifndef Vector3_HPP
#define Vector3_HPP

namespace GejbEngine {
	class Vector3 {
	private:
		double x, y, z;

	public:
		Vector3();
		Vector3(const Vector3 &v);
		Vector3(double x, double y, double z = 0);
		virtual ~Vector3();

		void Set(double xValue, double yValue, double zValue = 0);
		void Set(const Vector3 &v);
		double getX() const{
			return x;
		}
		double getY() const{
			return y;
		}
		double getZ() const{
			return z;
		}
		void setX(double value) {
			x = value;
		}
		void setY(double value) {
			y = value;
		}
		void setZ(double value) {
			z = value;
		}
		void Move(double dx, double dy, double dz = 0);

		void operator+=(const Vector3 &v);
		void operator-=(const Vector3 &v);
		void operator*=(const Vector3 &v);
		void operator/=(const Vector3 &v);
		bool operator==(const Vector3 &v) const;
		bool operator!=(const Vector3 &v) const;
		Vector3 &operator=(const Vector3 &v);

		Vector3 operator+(const Vector3 &v) const;
		Vector3 operator-(const Vector3 &v) const;

		double Distance(const Vector3 &v) const;
		double Length() const;
		double DotProduct(const Vector3 &v) const;
		Vector3 Normal() const;
	};
}

#endif