#pragma once
#include <memory>
#include <string>

namespace draw {
	class TransformMatrix;
	class Transform {
	public:
		// combine another transform object
		virtual const Transform operator*(const Transform&) const;
		virtual ~Transform() = default;
	protected:
		// copy constructor
		Transform(const Transform&, const bool = false);
		explicit Transform(const std::string&);
		const std::unique_ptr<TransformMatrix> transMatrix;
	private:
		const std::string name;
		friend std::ostream& operator<< (std::ostream&, const Transform&);
	};
}