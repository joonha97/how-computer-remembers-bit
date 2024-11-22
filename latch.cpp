#include <iostream>

class AndGate
{
public:
    bool exec(bool a, bool b)
    {
        return a & b;
    }
};

class NandGate
{
public:
    bool exec(bool a, bool b)
    {
        return not(a & b);
    }
};

class OrGate
{
public:
    bool exec(bool a, bool b)
    {
        return a || b;
    }
};

int main(void)
{
    //
    // test combination
    //
    std::cout << "\n[--- test combination ---]" << std::endl;
    AndGate and1;
    OrGate or1;
    bool a = true, b = false, c = false;
    std::cout << std::boolalpha << or1.exec((and1.exec(a, b)), c) << std::endl;

    //
    // OR latch ... simplest memory ... permenantly remembers [in]'s experience to be true
    //
    std::cout << "\n[--- OR latch ---]" << std::endl;
    OrGate or2;
    bool in = false, out = false;
    out = or2.exec(in, out);
    std::cout << std::boolalpha << out << std::endl;
    in = true;
    out = or2.exec(in, out);
    std::cout << std::boolalpha << out << std::endl;
    in = false;
    out = or2.exec(in, out);
    std::cout << std::boolalpha << out << std::endl; // still true

    //
    // S-R latch ... 1 bit memory ... can set and reset [q]
    //
    std::cout << "\n[--- S-R latch ---]" << std::endl;
    NandGate nand1, nand2;
    bool setbar = false, resetbar = false, q = false, qbar = false;

    q = nand1.exec(setbar, qbar);
    qbar = nand2.exec(q, resetbar);
    std::cout << std::boolalpha << "\nq: " << q << std::endl;
    std::cout << std::boolalpha << "qbar: " << qbar << std::endl;

    q = nand1.exec(setbar, qbar);
    qbar = nand2.exec(q, resetbar);
    std::cout << std::boolalpha << "\nq: " << q << std::endl;
    std::cout << std::boolalpha << "qbar: " << qbar << std::endl;

    setbar = true;
    q = nand1.exec(setbar, qbar); // q should be modified first and then feedbacked to nand2
    qbar = nand2.exec(q, resetbar);
    std::cout << std::boolalpha << "\nset!\nq: " << q << std::endl;
    std::cout << std::boolalpha << "qbar: " << qbar << std::endl;

    q = nand1.exec(setbar, qbar);
    qbar = nand2.exec(q, resetbar);
    std::cout << std::boolalpha << "\nremember?\nq: " << q << std::endl;
    std::cout << std::boolalpha << "qbar: " << qbar << std::endl;

    resetbar = true, setbar = false; // both cannot be true at the same time
    qbar = nand2.exec(q, resetbar);  // qbar should be modified first and then feedbacked to nand1
    q = nand1.exec(setbar, qbar);
    std::cout << std::boolalpha << "\nreset!\nq: " << q << std::endl;
    std::cout << std::boolalpha << "qbar: " << qbar << std::endl;

    resetbar = false;
    qbar = nand2.exec(q, resetbar);
    q = nand1.exec(setbar, qbar);
    std::cout << std::boolalpha << "\nq: " << q << std::endl;
    std::cout << std::boolalpha << "qbar: " << qbar << std::endl;

    return 0;
}