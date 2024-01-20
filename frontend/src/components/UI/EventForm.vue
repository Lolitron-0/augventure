<template>
  <router-link style="text-decoration: none" :to="{ name: 'eventsMain' }">
    <div class="event_form" id="event-form">
      <div class="body_event" id="body_event">
        <div class="title_event" id="title-event">Event3</div>
        <div class="description_event" id="description_event">My cool short description</div>
        <div class="content_event" id="content_event">
          <div class="content_art" id="content_art">art</div>
          <div class="content_boobs" id="content_boobs">boobs</div>
          <div class="content_tag" id="content_tag">long long tag</div>
        </div>
        <div class="stars_event" id="stars_event">
          <i class='bx bxs-star'></i>
          98
        </div>
      </div>
      <div class="state_event" id="state_event">
        Timed event!
        02:39:01
        remaining
      </div>
    </div>
  </router-link>
</template>

<script>
export default {

}
</script>

<style scoped>

.event_form {
  color: #cfcfcf;
  display: flex;
  justify-content: space-between;
  width: 95%;
  height: 130px;
  margin: 5px;
  border: .4px solid #858585;
  border-radius: 5px;
  padding: 5px;
  gap: 5px;
}
.state_event{
  display: flex;
  flex-direction: column;
  width: 30%;
  //border: 1px solid green;
  font-size: 16px;
  justify-content: center;
  align-items: center;

}
.body_event{
  //border: 1px solid green;
  width: 70%;
  font-size: 14px;
  align-items: center;
  padding: 5px;
}
.content_event{
  display: flex;
  justify-content: left;
  gap: 10px;
  color: #858585;
  padding-bottom: 10px;
}
.title_event{
  color: #0e73bd;
  font-size: 16px;
  padding-bottom: 10px;
}
.description_event{
  color: #858585;
  padding-bottom: 10px;
}
.stars_event{
  display: flex;
  gap: 5px;
  padding-bottom: 10px;
  font-size: 16px;
}
.content_art, .content_boobs, .content_tag{
  border: 1px solid #858585;
  border-radius: 10px;
  padding: 2px 7px;
}

@media (max-width: 1300px) {
  .title_event{
    font-size: 14px;
  }
  .state_event{
    font-size: 14px;
  }
  .content_event{
    font-size: 12px;
  }
  .description_event{
    font-size: 14px;
  }
  .stars_event{
    font-size: 14px;
  }
}

@media (max-width: 1150px) {
  .state_event{
    width: 27%;

  }
  .body_event{
    width: 73%;
  }
  .state_event{
    font-size: 12px;
  }
}
@media (max-width: 992px) {
  .state_event{
    width: 40%;
  }
  .body_event{
    width: 60%;
  }
  .state_event{
    font-size: 18px;
  }
  .title_event{
    font-size: 18px;
  }
  .content_event{
    font-size: 16px;
  }
  .description_event{
    font-size: 16px;
  }
  .stars_event{
    font-size: 18px;
  }

}
@media (max-width: 768px) {
  .event_form{
    width: 98%;
  }
  hr{
    display: none;
  }
}
@media (max-width: 430px) {
  .event_form{
    width: 98%;
  }
}
</style>