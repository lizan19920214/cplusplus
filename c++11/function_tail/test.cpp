/**
 * 函数拖尾返回类型
*/

//在c++中，我们使用模板可能会遇到下面的问题，使用模板需要返回值的类型，如下我们指定了返回类型为R
template<typename R, typename T, typename U>
R add(T x, U y) {
    return x+y;
}

//但是这种写法会很丑陋，在c++11中我们可以这样写
// template<typename R, typename T, typename U>
// decltype(x+y) add(T x, U y) {
//     return x+y;
// }

//但是如上是无法通过编译的， 因为在编译器读取到decltype(x+y) 时，x 和 y 尚未被定义。
// 为了解决这个问题，C++11 还引入了一个叫做拖尾返回类型（trailing return type），利用 auto 关键字将返回类型后置：

template<typename T, typename U>
auto add(T x, U y) -> decltype(x+y) {
    return x+y;
}

// 从 C++14 开始是可以直接让普通函数具备返回值推导，因此下面的写法变得合法：
template<typename T, typename U>
auto add(T x, U y) {
    return x+y;
}

