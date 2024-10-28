#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class PSO{
public:
    //粒子类
    class Particle {
    public:
        int position;//粒子的位置
        int velocity;//粒子的速度
        int bestPosition;//粒子的历史最佳位置

        Particle(int pos, int vel) : position(pos), velocity(vel), bestPosition(pos) {}
    };

    int pSize;//种群大小
    int maxGen;//最大迭代次数
    double iWeight;//惯性权重
    double ac1;//加速度1（向自己最优解靠近的速度）
    double ac2;//加速度2（向全局最优解靠近的速度）

    PSO(): pSize(10), maxGen(100), iWeight(0.5), ac1(1.5), ac2(1.5){}

    //适应度函数，y = x^2
    int fitness(int x) {
        return x * x;
    }

    //粒子群优化算法
    int pso() {
        vector<Particle> swarm;
        int globalBestPosition = 0;//全局最佳位置

        //初始化粒子群
        for (int i = 0; i < pSize; ++i) {
            int position = rand() % 32;   //初始化粒子位置，0 <= x <= 31
            int velocity = rand() % 5 - 2; //初始化粒子速度，取值范围在 [-2, 2]
            swarm.push_back(Particle(position, velocity));
            if (fitness(position) > fitness(globalBestPosition)) {
                globalBestPosition = position;
            }
        }

        //开始迭代
        for (int i = 0; i < maxGen; ++i) {
            for (int j = 0; j < pSize; ++j) {
                Particle &p = swarm[j];

                //更新粒子的速度
                int newVelocity = iWeight * p.velocity + ac1 * ((rand() % 100) / 100.0) * (p.bestPosition - p.position) + ac2 * ((rand() % 100) / 100.0) * (globalBestPosition - p.position);

                //更新粒子的位置
                p.velocity = newVelocity;
                p.position += p.velocity;

                //确保粒子位置在合法范围内
                if (p.position < 0) p.position = 0;
                if (p.position > 31) p.position = 31;

                //更新粒子的历史最佳位置
                if (fitness(p.position) > fitness(p.bestPosition)) {
                    p.bestPosition = p.position;
                }

                //更新全局最佳位置
                if (fitness(p.bestPosition) > fitness(globalBestPosition)) {
                    globalBestPosition = p.bestPosition;
                }
            }
        }

        return globalBestPosition; //返回全局最佳位置
    }

    void pso_run(){
        srand(time(0)); //设置随机数种子

        cout<<"粒子群算法"<<endl;
        //输入算法参数
//        cout << "输入种群大小、最大迭代次数、惯性权重、加速度1、加速度2：" << endl;
//        cin >> pSize >> maxGen >> iWeight >> ac1 >> ac2;

        //执行粒子群优化算法
        int bestPosition = pso();
        cout << "函数最大值：" << fitness(bestPosition) << endl; //输出最大值（y = x^2 的值）
    }

};


int main() {
    PSO pso;
    pso.pso_run();
    return 0;
}