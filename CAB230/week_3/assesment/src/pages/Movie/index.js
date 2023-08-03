import React, { useEffect, useState } from "react";
import { useNavigate, useSearchParams } from "react-router-dom";
import { getMovieDetails } from "../../utils/movieApi";
import { Label } from "reactstrap";
import { AgGridReact } from "ag-grid-react";

const genreColours = {
  Drama: { background: "cyan", color: "black" },
  Crime: { background: "purple", color: "white" },
  Comedy: { background: "orange", color: "black" },
  Action: { background: "red", color: "white" },
  Thriller: { background: "darkblue", color: "white" },
  Romance: { background: "orchid", color: "black" },
  Fantasy: { background: "gold", color: "black" },
  Adventure: { background: "green", color: "black" },
  "Sci-Fi": { background: "silver", color: "black" },
  Biography: { background: "white", color: "black" },
  Horror: { background: "black", color: "white" },
  Mystery: { background: "gray", color: "white" },
};

function Movie() {
  let navigate = useNavigate();
  const [movieData, setMovieData] = useState({ loading: true, data: {} });
  const [searchParams] = useSearchParams();

  const columns = [
    { headerName: "Name", field: "name" },
    { headerName: "Category", field: "category" },
    { headerName: "Characters", field: "characters" },
  ];

  useEffect(
    () => getMovieDetails(searchParams.get("imdbID"), setMovieData),
    [searchParams]
  );

  return (
    <>
      {movieData.loading ? (
        <Label>Loading</Label>
      ) : (
        <div>
          <div className="row">
            <h1>{movieData.data.title}</h1>
          </div>
          <div className="row">
            <div className="col text-start">
              <h3>Year Released: {movieData.data.year}</h3>
              <h3>Runtime: {movieData.data.runtime} min</h3>
              <h3>
                Genres:
                {movieData.data.genres.map((genre) => {
                  return (
                    <label
                      key={genre}
                      className={"genreLabel"}
                      style={genreColours[genre]}
                    >
                      {genre}
                    </label>
                  );
                })}
              </h3>
              <h3>Country: {movieData.data.country}</h3>
              <h3>
                Box Office: ${movieData.data.boxoffice.toLocaleString()} USD
              </h3>
              <div className="row">
                {movieData.data.ratings.map((rating) => {
                  return (
                    <div className="row" key={rating.source}>
                      <div className="col">
                        <Label key={rating.source}>{`${rating.source}:`}</Label>
                      </div>
                      <div className="col">
                        <Label key={rating.source}>{`${
                          rating.value ?? "Not Found"
                        }`}</Label>
                      </div>
                    </div>
                  );
                })}
              </div>
            </div>
            <div className="col">
              <img src={movieData.data.poster} alt="Movie Poster" />
            </div>
          </div>
          <p>{movieData.data.plot}</p>
          <div
            className="ag-theme-balham-dark"
            style={{ height: "400px", width: "auto" }}
          >
            <AgGridReact
              columnDefs={columns}
              rowData={movieData.data.principals}
              onRowClicked={(row) =>
                navigate(`/movies/person?id=${row.data.id}`)
              }
            />
          </div>
        </div>
      )}
    </>
  );
}

export default Movie;
