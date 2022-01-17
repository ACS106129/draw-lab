#pragma once
#include "../Matrix.h"

namespace draw {
	class Transform;
	class TransformMatrix : public Matrix {
	public:
		// copy constructor
		TransformMatrix(const TransformMatrix&);
		explicit TransformMatrix(const std::shared_ptr<const Transform> = nullptr);
		virtual void reset() override;
		void transform(const std::shared_ptr<const Transform>);
		const std::vector<std::shared_ptr<const Transform>>& getTransforms() const;
	private:
		std::vector<std::shared_ptr<const Transform>> transforms;
	};
}
