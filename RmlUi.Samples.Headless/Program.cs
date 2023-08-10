using RmlUi;
using RmlUi.Samples.Headless;

using var systemInterface = new HeadlessSystemInterface();

Rml.SetSystemInterface(systemInterface);

Rml.Initialise();

Rml.Shutdown();