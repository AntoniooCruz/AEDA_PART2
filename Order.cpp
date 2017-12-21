#include <vector>

using namespace std;

/**
 * @brief Compares the id's of 2 pointers of type T
 * @tparam T Pointer of object that has the  member function getId() defined: flights, planes, passengers
 * @param x1 The pointer to the first object
 * @param x2 The pointer to the second object
 * @return true, if the first object has a smaller id, false, otherwise
 */
template <typename T>
bool idOrder (T &x1, T &x2) {
    return x1->getId() < x2->getId();
}

/**
* @brief Calculates the smaller id the object could have different from any other object's id. If there're planes with the ids 1 and 3 but not 2, the function will return 2
* @tparam T Pointer of object that has the  member function getId() and not a static member value: planes, passengers
* @param x1 The pointer to the first object
* @param x2 The pointer to the second object
* @return the smaller id that is not yet taken
*/
template <typename T>
long nextId (const vector <T> &all) {

    if (all[0]->getId() != 1)
        return 0;

    for (int i = 0; i < all.size() - 1; i++) {

        if (all[i]->getId() != (all[i+1]->getId()-1))
            return i;
    }

    return all.size() - 1;
}