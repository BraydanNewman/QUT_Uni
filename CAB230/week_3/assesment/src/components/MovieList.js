import React, { useEffect, useState } from "react";
import { Label } from "reactstrap";
import { getMovieList } from "../utils/movieApi";
import { AgGridReact } from "ag-grid-react";
import "ag-grid-community/styles/ag-grid.css";
import "ag-grid-community/styles/ag-theme-balham.css";
import { InfiniteRowModelModule } from "@ag-grid-community/infinite-row-model";
import { useNavigate } from "react-router-dom";
import { ModuleRegistry } from "@ag-grid-community/core";

ModuleRegistry.registerModules([InfiniteRowModelModule]);

function MovieList(props) {
  let navigate = useNavigate();

  const columns = [
    { headerName: "Title", field: "title" },
    { headerName: "Year", field: "year" },
    { headerName: "Imdb Rating", field: "imdbRating" },
    { headerName: "Rotten Tomatoes Rating", field: "rottenTomatoesRating" },
    { headerName: "Metacritic Rating", field: "metacriticRating" },
    { headerName: "Classification", field: "classification" },
  ];

  useEffect(() => {
    getMovieList(
      props.MovieSearchParams.searchString,
      props.MovieSearchParams.searchYear,
      1,
      (data) => {
        setMovieData(data);
      }
    );
  }, [props.MovieSearchParams]);

  const [movieData, setMovieData] = useState({
    data: [],
    loading: false,
  });

  return (
    <>
      {movieData.loading ? (
        <Label>Loading</Label>
      ) : (
        <div
          style={{ height: "500px", width: "100%" }}
          className="ag-theme-balham-dark"
        >
          <AgGridReact
            pagination={true}
            columnDefs={columns}
            rowData={movieData.data}
            onRowClicked={(row) =>
              navigate(`/movies/movie?imdbID=${row.data.imdbID}`)
            }
          />
        </div>
      )}
    </>
  );
}

export default MovieList;
