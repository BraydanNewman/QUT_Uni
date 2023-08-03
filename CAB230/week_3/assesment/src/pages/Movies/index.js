import React, { useState } from "react";
import { Button, Form, FormGroup, Input, Label } from "reactstrap";
import YearDropdown from "../../components/yearsDropdown";
import MovieList from "../../components/MovieList";

function Movies() {
  const [MovieSearchParams, setMovieSearch] = useState({
    searchString: "",
    searchYear: "",
  });
  const [searchString, setSearchString] = useState("");
  const [searchYear, setSearchYear] = useState("");

  return (
    <>
      <Form
        className="inputForm"
        onSubmit={(event) => {
          event.preventDefault();
          setMovieSearch({
            searchString: searchString,
            searchYear: searchYear,
          });
        }}
      >
        <FormGroup>
          <Label>Movies Containing</Label>
          <Input
            type="text"
            onChange={(e) => setSearchString(e.target.value)}
          />
        </FormGroup>
        <FormGroup>
          <Label>From Date</Label>
          <br />
          <YearDropdown setYear={setSearchYear} />
        </FormGroup>
        <FormGroup>
          <Button
            onClick={() =>
              setMovieSearch({
                searchString: searchString,
                searchYear: searchYear,
              })
            }
          >
            Search
          </Button>
        </FormGroup>
      </Form>
      <MovieList MovieSearchParams={MovieSearchParams} />
    </>
  );
}

export default Movies;
