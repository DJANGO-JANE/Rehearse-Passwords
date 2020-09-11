#pragma once

#include <iostream>
#include <djcrypt.h>
#include <vector>
namespace djane
{
	/// <summary>
	/// Contains operations to get data from file as well as validation checking.
	/// </summary>
	
	static std::string _path,_app_dir;
	
	class Operations
	{

	protected:
		/// <summary>
		/// Retrieve file size to determine if a migration is needed.
		/// </summary>
		/// <param name="path">Path to the file.</param>
		/// <returns>Size of file.</returns>
		int GetFileSize(std::string path);
	private:
		djane::DjaneCryption* SecureChannel;

	public:
		///// <summary>
		///// Account or service provider.
		///// </summary>
		//std::string account;

		Operations(djane::DjaneCryption* secureChannel)
		{
			this->SecureChannel = secureChannel;
		}

		///// <summary>
		///// Password entered by the user.
		///// </summary>
		//std::string value;

		/// <summary>
		/// Gets the account name to prompt user for appropriate password.
		/// </summary>
		/// <returns>Returns a string of the account name.</returns>
		std::string getPasswordHint();

		/// <summary>
		/// Performs validation operations.
		/// </summary>
		/// <param name="account">: The account name.</param>
		/// <param name="value">: The text entered by user.</param>
		/// <returns>True if the password was correct for the specified account.</returns>
		bool checkPassword(std::string account, std::string value);

		/// <summary>
		/// Adds new account and password to text file.
		/// </summary>
		/// <param name="account">: The account name.</param>
		/// <param name="value">: The text entered by user.</param>
		/// <returns>True if write was successful.</returns>
		bool addRecordToFile(std::string account, std::string pass);

		/// <summary>
		/// Records progress with individual records.
		/// </summary>
		/// <param name="account">: The account name.</param>
		/// <param name="point">: Adds 1 point to the progress points.</param>
		/// <param name="attempt">: Adds 1 to the number of attempts made on memorising current password.</param>
		void WriteToRecord(std::string account, int point, int attempt);

		/// <summary>
		/// Changed the current working directory to a specified directory.
		/// </summary>
		/// <param name="ndir">: New Directory path</param>
		void WorkingDirectoryCheck(std::string ndir);

		bool RemoveAppFile();


		void ProgressReport(bool showOrNot, std::vector<std::string> courier);
	};
}

