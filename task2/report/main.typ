#import "conf.typ": conf
#import "@preview/lilaq:0.5.0" as lq
#show: conf.with(
  title: [Сравнение времени работы сортировок],
  type: "pract",
  info: (
    author: (
      name: [Тюменцева Радомира Александровича],
      faculty: [КНиИТ],
      group: "251",
      sex: "male",
    ),
    inspector: (
      degree: "старший преподаватель",
      name: "М. И. Сафрончик",
    ),
  ),
  settings: (
    title_page: (
      enabled: true,
    ),
    contents_page: (
      enabled: false,
    ),
  ),
)

#let xs = (50000, 100000, 500000, 1000000)

#lq.diagram(
  width: 100%,
  height: 50%,
  title: [Сравнение времени работы сортировок],
  xlabel: [Размер массива],
  ylabel: [Время выполнения],
  legend: (position: bottom + right),

  lq.plot(
    xs,
    (10.0358, 20.9653, 111.191, 225.738),
    mark: "o",
    label: [Quick sort],
  ),
  lq.plot(
    xs,
    (18.7245, 40.3204, 233.898, 500.421),
    mark: "s",
    label: [Heap sort],
  ),
  lq.plot(
    xs,
    (39.2332, 81.1335, 438.537, 906.662),
    mark: "d",
    label: [Merge sort],
  ),
)
