// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <vector>

/*
 C -> copy
 M -> movement
 D -> definition
 */

int num_of_new_int = 0;
int num_of_delete = 0;
int num_of_const_d = 0;
int num_of_const_c = 0;
int num_of_const_m = 0;
int num_of_assig_c = 0;
int num_of_assig_m = 0;
int num_of_dest = 0;

void reset_stats() {
	num_of_new_int = 0;
	num_of_delete = 0;
	num_of_const_d = 0;
	num_of_const_c = 0;
	num_of_const_m = 0;
	num_of_assig_c = 0;
	num_of_assig_m = 0;
	num_of_dest = 0;
}

void print_stats() {
	std::cout << "--------------" << std::endl;
	std::cout << "new int: " << num_of_new_int << std::endl;
	std::cout << "del int: " << num_of_delete << std::endl;
	std::cout << "const_d: " << num_of_const_d << std::endl;
	std::cout << "const_c: " << num_of_const_c << std::endl;
	std::cout << "const_m: " << num_of_const_m << std::endl;
	std::cout << "assig_c: " << num_of_assig_c << std::endl;
	std::cout << "assig_m: " << num_of_assig_m << std::endl;
	std::cout << "--------------" << std::endl;

}

class A {
public:
	int* p;

	A(int n) {
		p = new int(n);
		num_of_new_int++;
		num_of_const_d++;
		std::cout << "Define. const. *p=" << *p << std::endl;
	}

	A(const A& o) {
		p = new int(*o.p);
		num_of_new_int++;
		num_of_const_c++;
		std::cout << "Copy. const. *p=" << *p << ", copied " << &o << " to "
			<< this << std::endl;
	}

	A(A&& o) noexcept {
		p = o.p;
		o.p = nullptr;
		num_of_const_m++;
		std::cout << "Move. const. *p=" << *p << ", moved " << &o << " to "
			<< this << std::endl;
	}

	A& operator=(const A& o) {
		if (p != nullptr) { // we have something in p, we should release it first
			delete p;
			num_of_delete++;
		}

		if (o.p == nullptr)
			p = nullptr;
		else
			p = new int(*o.p);

		num_of_new_int++;
		num_of_assig_c++;
		std::cout << "Copy. assign. *p=" << *p << ", copied " << &o << " to "
			<< this << std::endl;
		return *this;
	}

	A& operator=(A&& o) noexcept {
		if (p != nullptr) { // we have something in p, we should release it first
			delete p;
			num_of_delete++;
		}
		p = o.p;
		o.p = nullptr;
		num_of_assig_m++;
		std::cout << "Move. assign. *p=" << *p << ", moved " << &o << " to "
			<< this << std::endl;
		return *this;
	}

	~A() {
		std::cout << "Destructor." << std::endl;
		num_of_dest++;
		if (p != nullptr) {
			num_of_delete++;
			delete p;
		}
	}

	operator int() const {
		return *p;
	}

};

template<typename T>
void print_vector(const std::vector<T>& v) {
	for (const T& a : v) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
}

void test0() {
	
	 /// La diferencia entre push_back y emplace_back:

	 // 1. Ejecutarlos e inspeccionar el resultado de print_stats para entender la diferencia entre ellos.

	/*
	 Define. const. *p=1
	 Move. const. *p=1, moved 000000AFA48FFBF8 to 000001CD97E22A30
	 Destructor.
	 Destructor.
	 --------------
	 new int: 1
	 del int: 1
	 const_d: 1
	 const_c: 0
	 const_m: 1
	 assig_c: 0
	 assig_m: 0
	 -------------- 
	std::vector<A> v;
	v.push_back(A(1));

	Explicación: crea la variable y hace push_back al vector. La variable se mueve.
	*/

	/*
	 Define. const. *p=1
	 Copy. const. *p=1, copied 000000DB83BBFA78 to 0000025FC9972C30
	 Destructor.
	 Destructor.
	 --------------
	 new int: 2
	 del int: 2
	 const_d: 1
	 const_c: 1
	 const_m: 0
	 assig_c: 0
	 assig_m: 0
	 -------------- 
	std::vector<A> v;
	A x(1);
	v.push_back(x);

	Explicación: crea la variable, la mete a la constructora (se define una vez pero crea dos variables internamente) y la copia en el vector.
	*/

	/*
	 Define. const. *p=1
	 Move. const. *p=1, moved 000000026B2FFA78 to 000001E11CF32870
	 Destructor.
	 Destructor.
	 --------------
	 new int: 1
	 del int: 1
	 const_d: 1
	 const_c: 0
	 const_m: 1
	 assig_c: 0
	 assig_m: 0
	 --------------
	std::vector<A> v;
	A x(1);
	v.push_back(std::move(x));

	Explicación: como le fuerza el movimiento, ocurre como en el primer ejemplo, se mueve y solo crea una variable internamente.
	*/

	/*
	 Define. const. *p=1
	 Destructor.
	 --------------
	 new int: 1
	 del int: 1
	 const_d: 1
	 const_c: 0
	 const_m: 0
	 assig_c: 0
	 assig_m: 0
	 -------------- 
	std::vector<A> v;
	v.emplace_back(1);

	Explicación: es la forma óptima de los cuatro ejemplos, solo define una vez la variable, crea el int y lo borra, solo se llama al constructor una vez
	mientras que en los otros ejemplos se llama dos veces. No hay ni movimiento ni copia, pero funciona.
	*/

	// 2. Quita la constructora de movimiento de la clase A (ponla en comentario), y ejecutarlos e inspeccionar el resultado de print_stats comparándolos con los del apartado anterior.

	/*
	 Define. const. *p=1
	 Copy. const. *p=1, copied 00000095C94FF808 to 000001BB53F42CB0
	 Destructor.
	 Destructor.
	 --------------
	 new int: 2
	 del int: 2
	 const_d: 1
	 const_c: 1
	 const_m: 0
	 assig_c: 0
	 assig_m: 0
	 --------------
	std::vector<A> v;
	v.push_back(A(1));

	Explicación: dado que no puede moverlo, lo copia, y por tanto gasta mayor número de recursos: 2 ints en lugar de 1.
	*/

	/*
	 Define. const. *p=1
	 Copy. const. *p=1, copied 000000A95678F788 to 00000261C29731B0
	 Destructor.
	 Destructor.
	 --------------
	 new int: 2
	 del int: 2
	 const_d: 1
	 const_c: 1
	 const_m: 0
	 assig_c: 0
	 assig_m: 0
	 --------------
	std::vector<A> v;
	A x(1);
	v.push_back(x);

	Explicación: en este caso gasta lo mismo porque antes usaba el constructor de copia y ahora también
	*/

	/*
	 Define. const. *p=1
	 Copy. const. *p=1, copied 000000DEE335FBE8 to 000002640C5E1F60
	 Destructor.
	 Destructor.
	 --------------
	 new int: 2
	 del int: 2
	 const_d: 1
	 const_c: 1
	 const_m: 0
	 assig_c: 0
	 assig_m: 0
	 --------------
	std::vector<A> v;
	A x(1);
	v.push_back(std::move(x));

	Explicación: le fuerza el movimiento, pero no hay constructora de movimiento, por tanto, lo hace por copia y gasta mayor número de recursos.
	*/

	/*
	 Define. const. *p=1
	 Destructor.
	 --------------
	 new int: 1
	 del int: 1
	 const_d: 1
	 const_c: 0
	 const_m: 0
	 assig_c: 0
	 assig_m: 0
	 --------------
	std::vector<A> v;
	v.emplace_back(1);

	Explicación: está igual que antes porque no usa el movimiento ni la copia, el emplace_back tiene funcionalidad propia y no va por constructoras, en definitiva, lo mejor y más óptimo.
	*/

	/// Lo que cuesta redimensionar la memoria.

	std::vector < A > v;
	v.reserve(20);

	for (int i = 0; i < 10; i++) {
		std::cout << "# adding " << i << " using emplace_back" << std::endl;
		if (v.capacity() == v.size()) {
			std::cout << "# The vector is about to be resized!" << std::endl;
		}
		v.emplace_back(i);
	}

	// 1. Ejecutar el código como está arriba sin/con la constructora de movimiento
	// CON:

	/*
		# adding 0 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=0
		# adding 1 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=1
		Move. const. *p=0, moved 000001BE7E6E2780 to 000001BE7E6E2280
		Destructor.
		# adding 2 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=2
		Move. const. *p=0, moved 000001BE7E6E2280 to 000001BE7E6E0ED0
		Move. const. *p=1, moved 000001BE7E6E2288 to 000001BE7E6E0ED8
		Destructor.
		Destructor.
		# adding 3 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=3
		Move. const. *p=0, moved 000001BE7E6E0ED0 to 000001BE7E6E0510
		Move. const. *p=1, moved 000001BE7E6E0ED8 to 000001BE7E6E0518
		Move. const. *p=2, moved 000001BE7E6E0EE0 to 000001BE7E6E0520
		Destructor.
		Destructor.
		Destructor.
		# adding 4 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=4
		Move. const. *p=0, moved 000001BE7E6E0510 to 000001BE7E6E10B0
		Move. const. *p=1, moved 000001BE7E6E0518 to 000001BE7E6E10B8
		Move. const. *p=2, moved 000001BE7E6E0520 to 000001BE7E6E10C0
		Move. const. *p=3, moved 000001BE7E6E0528 to 000001BE7E6E10C8
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		# adding 5 using emplace_back
		Define. const. *p=5
		# adding 6 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=6
		Move. const. *p=0, moved 000001BE7E6E10B0 to 000001BE7E6D3C90
		Move. const. *p=1, moved 000001BE7E6E10B8 to 000001BE7E6D3C98
		Move. const. *p=2, moved 000001BE7E6E10C0 to 000001BE7E6D3CA0
		Move. const. *p=3, moved 000001BE7E6E10C8 to 000001BE7E6D3CA8
		Move. const. *p=4, moved 000001BE7E6E10D0 to 000001BE7E6D3CB0
		Move. const. *p=5, moved 000001BE7E6E10D8 to 000001BE7E6D3CB8
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		# adding 7 using emplace_back
		Define. const. *p=7
		# adding 8 using emplace_back
		Define. const. *p=8
		# adding 9 using emplace_back
		# The vector is about to be resized!
		Define. const. *p=9
		Move. const. *p=0, moved 000001BE7E6D3C90 to 000001BE7E6DF1A0
		Move. const. *p=1, moved 000001BE7E6D3C98 to 000001BE7E6DF1A8
		Move. const. *p=2, moved 000001BE7E6D3CA0 to 000001BE7E6DF1B0
		Move. const. *p=3, moved 000001BE7E6D3CA8 to 000001BE7E6DF1B8
		Move. const. *p=4, moved 000001BE7E6D3CB0 to 000001BE7E6DF1C0
		Move. const. *p=5, moved 000001BE7E6D3CB8 to 000001BE7E6DF1C8
		Move. const. *p=6, moved 000001BE7E6D3CC0 to 000001BE7E6DF1D0
		Move. const. *p=7, moved 000001BE7E6D3CC8 to 000001BE7E6DF1D8
		Move. const. *p=8, moved 000001BE7E6D3CD0 to 000001BE7E6DF1E0
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		Destructor.
		--------------
		new int: 10
		del int: 10
		const_d: 10
		const_c: 0
		const_m: 25
		assig_c: 0
		assig_m: 0
		--------------

		//Duda: No entendemos por qué resizea en el 3, 6 y 9. ¿No debería resizear solo en el 0 (a 1), 1 (a 2), 2 (a 4), 4 (a 8) y 8 (a 16)?
		//Explicación: Pendiente de resolver duda
	*/	

	// SIN:

	/*
	# adding 0 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=0
	# adding 1 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=1
	Copy. const. *p=0, copied 0000028DA0CC6CD0 to 0000028DA0CC6D20
	Destructor.
	# adding 2 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=2
	Copy. const. *p=0, copied 0000028DA0CC6D20 to 0000028DA0CC5430
	Copy. const. *p=1, copied 0000028DA0CC6D28 to 0000028DA0CC5438
	Destructor.
	Destructor.
	# adding 3 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=3
	Copy. const. *p=0, copied 0000028DA0CC5430 to 0000028DA0CC5610
	Copy. const. *p=1, copied 0000028DA0CC5438 to 0000028DA0CC5618
	Copy. const. *p=2, copied 0000028DA0CC5440 to 0000028DA0CC5620
	Destructor.
	Destructor.
	Destructor.
	# adding 4 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=4
	Copy. const. *p=0, copied 0000028DA0CC5610 to 0000028DA0CC2C90
	Copy. const. *p=1, copied 0000028DA0CC5618 to 0000028DA0CC2C98
	Copy. const. *p=2, copied 0000028DA0CC5620 to 0000028DA0CC2CA0
	Copy. const. *p=3, copied 0000028DA0CC5628 to 0000028DA0CC2CA8
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	# adding 5 using emplace_back
	Define. const. *p=5
	# adding 6 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=6
	Copy. const. *p=0, copied 0000028DA0CC2C90 to 0000028DA0CBA280
	Copy. const. *p=1, copied 0000028DA0CC2C98 to 0000028DA0CBA288
	Copy. const. *p=2, copied 0000028DA0CC2CA0 to 0000028DA0CBA290
	Copy. const. *p=3, copied 0000028DA0CC2CA8 to 0000028DA0CBA298
	Copy. const. *p=4, copied 0000028DA0CC2CB0 to 0000028DA0CBA2A0
	Copy. const. *p=5, copied 0000028DA0CC2CB8 to 0000028DA0CBA2A8
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	# adding 7 using emplace_back
	Define. const. *p=7
	# adding 8 using emplace_back
	Define. const. *p=8
	# adding 9 using emplace_back
	# The vector is about to be resized!
	Define. const. *p=9
	Copy. const. *p=0, copied 0000028DA0CBA280 to 0000028DA0CBE080
	Copy. const. *p=1, copied 0000028DA0CBA288 to 0000028DA0CBE088
	Copy. const. *p=2, copied 0000028DA0CBA290 to 0000028DA0CBE090
	Copy. const. *p=3, copied 0000028DA0CBA298 to 0000028DA0CBE098
	Copy. const. *p=4, copied 0000028DA0CBA2A0 to 0000028DA0CBE0A0
	Copy. const. *p=5, copied 0000028DA0CBA2A8 to 0000028DA0CBE0A8
	Copy. const. *p=6, copied 0000028DA0CBA2B0 to 0000028DA0CBE0B0
	Copy. const. *p=7, copied 0000028DA0CBA2B8 to 0000028DA0CBE0B8
	Copy. const. *p=8, copied 0000028DA0CBA2C0 to 0000028DA0CBE0C0
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	--------------
	new int: 35
	del int: 35
	const_d: 10
	const_c: 25
	const_m: 0
	assig_c: 0
	assig_m: 0
	--------------

	Explicación: por copia es menor óptimo, porque requiere de muchos más recursos (35 variables en vez de 10) 
	*/

	//2. Añadir v.reserve(20) antes del bucle y ejecutalo (con la constructora de movimiento).

	/*
	# adding 0 using emplace_back
	Define. const. *p=0
	# adding 1 using emplace_back
	Define. const. *p=1
	# adding 2 using emplace_back
	Define. const. *p=2
	# adding 3 using emplace_back
	Define. const. *p=3
	# adding 4 using emplace_back
	Define. const. *p=4
	# adding 5 using emplace_back
	Define. const. *p=5
	# adding 6 using emplace_back
	Define. const. *p=6
	# adding 7 using emplace_back
	Define. const. *p=7
	# adding 8 using emplace_back
	Define. const. *p=8
	# adding 9 using emplace_back
	Define. const. *p=9
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	Destructor.
	--------------
	new int: 10
	del int: 10
	const_d: 10
	const_c: 0
	const_m: 0
	assig_c: 0
	assig_m: 0
	--------------

	Explicación: dado que no tiene que usar memoria para resizear, porque ya se ha reservado con anterioridad, todo es mucho más rápido y directo, y más óptimo.
	//Menos pasos, más eficiencia
	*/


}


int main(int, char**) {
	reset_stats();
	test0();
	print_stats();


	return 0;
}