#pragma once
namespace draw {
	/// <summary>
	/// As an interface to determine if object itself completed
	/// </summary>
	class ICompletable {
	public:
		/// <summary>
		/// Use to make the object done 
		/// </summary>
		virtual void done() = 0;
		/// <returns>Whether done or not</returns>
		virtual const bool isDone() const = 0;
	};
}
