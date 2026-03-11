#import "@preview/typslides:1.3.2": *

// Настройки шрифта и глобальных стилей
#set text(font: "PT Sans", size: 22pt)

#show: typslides.with(
  ratio: "4-3",
  theme: "reddy",
)

// --- СЛАЙД 1 ---
#front-slide(
  title: "AVL-деревья",
  subtitle: "Первая самобалансирующаяся структура",
  authors: "Тюменцев Р. А., 251 г.",
)

#slide(title: "Создатели")[
  #v(1fr)
  #v(1em)
  #set align(center)
  #figure(
    grid(
      columns: (1fr, 1fr),
      gutter: 2em,
      image("img/slide1-1.jpg", height: 70%),
      image("img/slide1-2.jpg", height: 70%),
    ),
    caption: [Г. Адельсон-Вельский и Е. Ландис],
  )
  #v(1fr)
]

// --- СЛАЙД 2 ---
#slide(title: "Проблема обычных деревьев поиска")[
  #grid(
    columns: (1.5fr, 1fr),
    gutter: 2em,
    [
      #set align(center)
      *BST на случайных данных*
      #v(1em)
      #image("img/slide3-1.png", height: 40%)
      #align(center)[Сложность: $O(log n)$]
    ],
    [
      #set align(center)
      *BST на отсортированных данных*
      #v(1em)
      #image("img/slide3-2.png", height: 40%)
      #align(center)[Сложность: $O(n)$]
    ],
  )
  #v(1em)
  #text(
    size: 18pt,
    fill: red.darken(20%),
  )[*Проблема:* Деградация дерева в связный список.]
]

// --- СЛАЙД 3 ---
#slide(title: "Принцип баланса")[
  #v(1fr)
  #align(center)[
    Определение фактора баланса для узла $v$:
    #v(0.5em)
    #block(fill: gray.lighten(90%), inset: 1em, radius: 5pt)[
      `BF(v) = height(left) - height(right)`
    ]

    #v(1em)
    *Условие AVL-сбалансированности:*
    #v(0.5em)
    #text(size: 30pt, weight: "bold", fill: blue)[$|B F(v)| <= 1$]

    #v(1em)
    Допустимые значения: $-1, 0, 1$
  ]
  #v(1fr)
  // Текст выступления: Про математический критерий «здоровья» дерева.
]

// --- СЛАЙД 4 ---
#slide(title: "Механика восстановления: Повороты")[
  #set align(center)
  #grid(
    columns: (1fr, 1fr),
    gutter: 1em,
    [
      *Одинарные (LL / RR)*
      #image("img/slide2-1.png", height: 40%)
      #text(size: 16pt)[Для внешних дисбалансов]
    ],
    [
      *Двойные (LR / RL)*
      #image("img/slide2-2.png", height: 40%)
      #text(size: 16pt)[Для внутренних изгибов («колено»)]
    ],
  )
  #v(1em)
  #align(center)[#text(weight: "bold")[Сложность операции: $O(1)$]]
  // Текст выступления: О том, что это всего лишь переброска указателей.
]

// --- СЛАЙД 5 ---
#slide(title: "Пример")[
  #figure(
    image("img/balancing.png", height: 95%),
    caption: [Вставка элемента 32 в дерево и последующая его балансировка],
  )
]

// --- СЛАЙД 6 ---
#slide(title: "Алгоритмическая сложность")[
  #align(center)[
    #table(
      columns: (1fr, 1fr, 1fr),
      inset: 10pt,
      align: horizon,
      [*Операция*], [*Среднее*], [*Худшее*],
      [Поиск], [$O(log n)$], [$O(log n)$],
      [Вставка], [$O(log n)$], [$O(log n)$],
      [Удаление], [$O(log n)$], [$O(log n)$],
    )
  ]

  #v(1em)
  #list(
    [Память: $O(n)$ для хранения узлов],
    [Накладные расходы: +1 поле для хранения высоты в узле],
  )
  // Текст выступления: Про гарантии стабильности в худшем случае.
]

// --- СЛАЙД 7 ---
#slide(title: "AVL vs Красно-черные деревья")[
  #v(0.4fr)
  #grid(
    columns: (1fr, 1fr),
    gutter: 2em,
    [
      *AVL-дерево*
      #list(
        [Строгий баланс],
        [Меньшая высота],
        [*Быстрее поиск*],
      )
    ],
    [
      *RB-дерево*
      #list(
        [Гибкий баланс],
        [Меньше поворотов],
        [*Быстрее запись*],
      )
    ],
  )
  #v(1fr)
  #align(center)[#text(
    style: "italic",
  )[«AVL для чтения, Красно-чёрное для записи»]]
  #v(0.4fr)
  // Текст выступления: Сравнение производительности и выбор структуры.
]

// --- СЛАЙД 8 ---
#slide(title: "Практическое применение")[
  #v(0.6fr)
  #list(
    [*Базы данных:* In-memory индексы (где поиск доминирует)],
    [*Системное ПО:* Библиотеки с гарантированным временем отклика],
    [*Real-time системы:* Там, где недопустимы просадки до $O(n)$],
    [*Словари:* Высоконагруженные ассоциативные массивы],
  )
  #v(1fr)
  // Текст выступления: Где в реальном мире встретить AVL.
]

// --- СЛАЙД 9 ---
#title-slide[
  Спасибо за внимание!
]
