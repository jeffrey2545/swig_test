public class Test {
    static {
        // Load the native library
        System.loadLibrary("CarWrapper");
        // System.load("/Users/Jeffrey/Desktop/python_test/libCarWrapper.dylib");
        // System.loadLibrary("libCarWrapper");
    }

    public static void main(String[] args) {
        CarWrapper wrapper = new CarWrapper();

        // Initialize Python interpreter
        wrapper.init_python();

        // Create a new Car object
        SWIGTYPE_p_PyObject carPtr = wrapper.Car_new("audi", "a4", 2019);

        // Use the Car object
        SWIGTYPE_p_PyObject carDescription = wrapper.Car_get_descriptive_name(carPtr);
        System.out.println(carDescription);

        wrapper.Car_update_odometer(carPtr, 23);
        wrapper.Car_read_odometer(carPtr);

        // Finalize the Python interpreter
        wrapper.finalize_python();
    }
}
