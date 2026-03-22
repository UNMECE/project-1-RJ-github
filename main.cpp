#include <iostream>
#include <vector>

struct Capacitor
{
    std::vector<double> time;
    std::vector<double> voltage;
    std::vector<double> current;
    double C;
};

Capacitor create_capacitor(int steps, double C)
{
    Capacitor cap;
    cap.C = C;

    cap.time.resize(steps);
    cap.voltage.resize(steps);
    cap.current.resize(steps);

    return cap;
}

int main()
{
    const double dt = 1e-10;
    const double final_time = 5e-6;
    const int steps = static_cast<int>(final_time / dt);

    const double R = 1e3;          // 1 kΩ
    const double C = 100e-12;      // 100 pF
    const double I_const = 1e-2;   // 10 mA
    const double V0 = 10.0;

    // Constant Current Case
    Capacitor cc = create_capacitor(steps, C);

    cc.time[0] = 0.0;
    cc.voltage[0] = 0.0;
    cc.current[0] = I_const;

    for (int i = 1; i < steps; i++)
    {
        cc.time[i] = i * dt;

        // Current stays constant
        cc.current[i] = I_const;

        // Voltage update
        cc.voltage[i] = cc.voltage[i-1] +
                        (cc.current[i-1] * dt) / cc.C;

        if (i % 200 == 0)
        {
            std::cout << "[Const Current] t=" << cc.time[i]
                      << " V=" << cc.voltage[i]
                      << " I=" << cc.current[i] << "\n";
        }
    }

    // Constant Voltage (RC Circuit)
    Capacitor cv = create_capacitor(steps, C);

    cv.time[0] = 0.0;
    cv.voltage[0] = 0.0;
    cv.current[0] = V0 / R;

    for (int i = 1; i < steps; i++)
    {
        cv.time[i] = i * dt;

        // Current decay
				cv.current[i] = cv.current[i-1] *
                (1.0 - dt / (R * cv.C));

        // Voltage update
        cv.voltage[i] = cv.voltage[i-1] +
                        (cv.current[i-1] * dt) / cv.C;

        if (i % 200 == 0)
        {
            std::cout << "[RC Circuit] t=" << cv.time[i]
                      << " V=" << cv.voltage[i]
                      << " I=" << cv.current[i] << "\n";
        }
    }

    return 0;
}
