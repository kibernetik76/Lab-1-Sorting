import pandas as pd
import matplotlib.pyplot as plt

# Читаем результаты, которые записала программа на C++
df = pd.read_csv('results.csv')

plt.figure(figsize=(10, 6))

# Рисуем только те строки, где время > 0 (алгоритмы O(n^2) не запускались для больших n)
plt.plot(df[df['Insertion'] > 0]['Size'], df[df['Insertion'] > 0]['Insertion'],
         marker='o', label='Insertion Sort  O(n²)')
plt.plot(df[df['Shaker'] > 0]['Size'],    df[df['Shaker'] > 0]['Shaker'],
         marker='s', label='Shaker Sort  O(n²)')
plt.plot(df['Size'], df['Merge'],   marker='^', label='Merge Sort  O(n·log n)')
plt.plot(df['Size'], df['StdSort'], marker='x', label='std::sort  O(n·log n)')

plt.title('Зависимость времени сортировки от размера массива')
plt.xlabel('Количество элементов (N)')
plt.ylabel('Время (мс)')
plt.legend()
plt.grid(True)
plt.yscale('log')   # Логарифмическая шкала — иначе merge и std::sort "прилипают" к нулю
plt.tight_layout()
plt.savefig('sorting_benchmark.png', dpi=150)
plt.show()
print("График сохранён в sorting_benchmark.png")