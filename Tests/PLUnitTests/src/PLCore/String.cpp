//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/String/String.h>
#include "UnitTest++AddIns/wchar_template.h"

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(String) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Array Test Fixture :)
	struct ConstructTest
	{
		ConstructTest() { 
			/* some setup */
		}
		~ConstructTest() {
			/* some teardown */
		}

		// Container for testing
		PLCore::String str;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		CHECK_EQUAL(0U, str.GetLength());
	}
}