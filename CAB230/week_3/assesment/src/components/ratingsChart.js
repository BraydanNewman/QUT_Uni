import React from "react";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Bar } from "react-chartjs-2";

ChartJS.register(
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
);

const options = {
  responsive: true,
  plugins: {
    legend: {
      position: "top",
    },
    title: {
      display: true,
      text: "Ratings At a Glance",
    },
  },
};

const labels = [
  "0 - 1",
  "1 - 2",
  "2 - 3",
  "3 - 4",
  "4 - 5",
  "5 - 6",
  "6 - 7",
  "7 - 8",
  "8 - 9",
  "9 - 10",
];

const formatRatingsData = (data) => {
  data = data.map((item) => `${Math.floor(item)}`);
  const formattedData = {};
  for (let index in labels) {
    formattedData[labels[index]] = data.filter((x) => x === index).length;
  }
  return formattedData;
};

function RatingsChart(props) {
  const data = {
    labels,
    datasets: [
      {
        label: "Count Of Rating in Groups",
        data: formatRatingsData(props.ratingsData),
        backgroundColor: "#3500d3",
      },
    ],
  };

  return <Bar options={options} data={data} />;
}

export default RatingsChart;
