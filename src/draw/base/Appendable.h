#pragma once
#include "../impl/ICompletable.h"
namespace draw {
	class Dot;
	class Appendable : public ICompletable {
	public:
		/// <summary>
		/// Save current position to buffer and wait to be appended, if done will ignore any buffer
		/// </summary>
		/// <param name="">X axis</param>
		/// <param name="">Y axis</param>
		void buffering(const int, const int);
		/// <summary>
		/// Save current position to buffer and wait to be appended, if done will ignore any buffer
		/// </summary>
		/// <param name="">Dot position</param>
		void buffering(const Dot&);
		/// <summary>
		/// Append object until done function called
		/// </summary>
		virtual void append() = 0;
		/// <summary>
		/// Once claimed to be done, will not able to be appended again
		/// </summary>
		virtual void done() override final;
		virtual const bool isDone() const override final;
		virtual ~Appendable() = default;
	protected:
		virtual bool doneFilter();
		virtual void bufferingImpl(const Dot&) = 0;
	private:
		bool d = false;
	};
}