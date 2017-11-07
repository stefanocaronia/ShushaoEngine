#pragma once

/* MACRO PER SIMULARE get; set; di C# si usa nell'header file all'interno della classe così:

	PROPERTY {
		GET(float) {
			return value / 3.0f;
		}
		SET(float) {
			value = f * 2.0f;
		}
	} testProp;


	class {
		protected:
			Transform* value;
		public:
			operator Transform* ();
			void Transform^
	} parent;
*/
#define PROPERTY	class Property
#define GET(TYPE, PARENT_TYPE) 	protected: TYPE value; PARENT_TYPE* parent; \
					public: Property(PARENT_TYPE* pa) {parent = pa;} \
					public: operator TYPE () const
#define SET(TYPE) 	public: void operator = (const TYPE param)


//#define SHADER_START() R"glsl(
//#define SHADER_END() )glsl";
