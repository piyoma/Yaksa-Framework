# Yaksa Framework

/*꧁༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༺TONOSHIKI PIYOMA༻༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒༒꧂
           
          ꧁༒༒༒༒༒༒༒༒༒༒༒༒༺☼☽☪☭----✞----☭☪☽☼༻༒༒༒༒༒༒༒༒༒༒༒༒꧂          

                A cross-platform GUI Framework Wrapped Chromium that Can embedded All Systems and Platforms.
                eg. Windows, linux, macOS, Android, iOS, Unity, UnrealEngine4, Qt, and etc.
                2020/04/29 piyoma
                break;
                ༺GitHub https://github.com/piyoma/YaksaFramework༻    
		
		
		
		
		
     			
		About Yaksa-Framework.h Unique Interface Define.
		
		///////////////////////////////////////༺TONOSHIKI PIYOMA///////////////////////////////////////


		This Header File implements Cross-platform Component  Design( -- call and sync-async callback -- ), 
		completely abstract,blocking the coupling between modules. 
		you can call a object simplely In any Operating Systems and Platforms, as follows:

		Foo foo;
		foo.Initialize();
		foo.asnyc_work(); // call a obj method like Yaksa.Module.Bar  or Yaksa.Module.Foo

		//Support Dynamic Load & Unload Components

		//At First should define a class like this
		//By the way, Yaksa Framework Unique Interface is Opensource code,  
		//Can Add/Extend  unlimited  C/C++ ComponentsExtensions Private or Public

		class Foo
		{
			public:
			Foo() {}
			~Foo(){}
			void asnyc_work()
			{
					
				if( component.Load(L"LocalPath", L"Yaksa.Module.Bar")  )
				{

					component.exec(value_param("FooObj"),
					value_param("bar"), 0,
					&Foo::Callee, this, 0);

				}

			}
			void Callee(type_char* obj, type_char* cmd, type_char* data_type,
					type_char* data, int len, int msgid)
			{
					//////////Do Some Asnyc Works//////////
			}

			private:
			SingleComponent<Foo>  component;
		};

		

		2020/05/01 piyoma


*/
