import React from "react";

function YearDropdown(props) {
  const firstMovie = 1988;
  const currentYear = new Date().getFullYear();
  const years = Array.from(
    new Array(currentYear - firstMovie),
    (val, index) => currentYear - index
  );
  years.unshift("");
  return (
    <select onChange={(e) => props.setYear(e.target.value)}>
      {years.map((year) => {
        return (
          <option key={`${year}`} value={`${year}`}>
            {year}
          </option>
        );
      })}
    </select>
  );
}

export default YearDropdown;
